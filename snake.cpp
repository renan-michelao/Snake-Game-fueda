// Implementação da Cobra

#include "snake.h"

Snake::Snake(int tamanhoBloco, int posX, int posY) : tamanhoBloco(tamanhoBloco), direcaoAtual(Direcao::DIREITA) {
    // Cria a cabeça da cobra
    sf::RectangleShape cabeca;
    cabeca.setSize(sf::Vector2f(tamanhoBloco, tamanhoBloco));
    cabeca.setFillColor(sf::Color::Green);
    cabeca.setPosition(posX, posY);
    segmentos.push_back(cabeca);
}

void Snake::mover() {
    if (direcaoAtual == Direcao::PARADO) return;
    
    // Move o corpo (do último segmento para o primeiro)
    for (size_t i = segmentos.size() - 1; i > 0; i--) {
        segmentos[i].setPosition(segmentos[i - 1].getPosition());
    }
    
    // Move a cabeça baseado na direção
    sf::Vector2f movimento(0, 0);
    switch (direcaoAtual) {
        case Direcao::CIMA: movimento.y = -tamanhoBloco; break;
        case Direcao::BAIXO: movimento.y = tamanhoBloco; break;
        case Direcao::DIREITA: movimento.x = tamanhoBloco; break;
        case Direcao::ESQUERDA: movimento.x = -tamanhoBloco; break;
    }
    segmentos[0].move(movimento);
}

void Snake::crescer() {
    sf::RectangleShape novoSegmento;
    novoSegmento.setSize(sf::Vector2f(tamanhoBloco, tamanhoBloco));
    novoSegmento.setFillColor(sf::Color::Green);
    novoSegmento.setPosition(segmentos.back().getPosition());
    segmentos.push_back(novoSegmento);
}

void Snake::mudarDirecao(Direcao novaDirecao) {
    // Previne movimento inverso (não pode ir de cima para baixo diretamente)
    if ((direcaoAtual == Direcao::CIMA && novaDirecao == Direcao::BAIXO) ||
        (direcaoAtual == Direcao::BAIXO && novaDirecao == Direcao::CIMA) ||
        (direcaoAtual == Direcao::DIREITA && novaDirecao == Direcao::ESQUERDA) ||
        (direcaoAtual == Direcao::ESQUERDA && novaDirecao == Direcao::DIREITA)) {
        return;
    }
    direcaoAtual = novaDirecao;
}

sf::Vector2f Snake::getPosicaoCabeca() const {
    return segmentos[0].getPosition();
}

bool Snake::colisaoComProprioCorpo() const {
    for (size_t i = 1; i < segmentos.size(); i++) {
        if (segmentos[0].getGlobalBounds().intersects(segmentos[i].getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

bool Snake::colisaoComParede(int larguraJanela, int alturaJanela) const {
    sf::Vector2f posicao = getPosicaoCabeca();
    return (posicao.x < 0 || posicao.x >= larguraJanela || 
            posicao.y < 0 || posicao.y >= alturaJanela);
}

bool Snake::colisaoComComida(const sf::RectangleShape& comida) const {
    return segmentos[0].getGlobalBounds().intersects(comida.getGlobalBounds());
}

void Snake::desenhar(sf::RenderWindow& janela) const {
    for (const auto& segmento : segmentos) {
        janela.draw(segmento);
    }
}