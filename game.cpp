// Implementação do Jogo

#include "game.h"
#include <random>
#include <iostream>

// Gerador de números aleatórios
std::random_device rd;
std::mt19937 gen(rd());

Game::Game(sf::RenderWindow& janela, Snake& cobra, const sf::Font& fonte) 
    : janela(janela), cobra(cobra), tempoPorMovimento(0.1f), pontuacao(0), fimDeJogo(false) {
    
    // Configura comida
    comida.setSize(sf::Vector2f(20, 20));
    comida.setFillColor(sf::Color::Red);
    comida.setPosition(100, 100);
    
    // Configura textos
    textoPontuacao.setFont(fonte);
    textoPontuacao.setCharacterSize(24);
    textoPontuacao.setFillColor(sf::Color::White);
    textoPontuacao.setPosition(10, 10);
    
    textoGameOver.setFont(fonte);
    textoGameOver.setCharacterSize(50);
    textoGameOver.setFillColor(sf::Color::Red);
}

void Game::processarEventos() {
    sf::Event evento;
    while (janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            janela.close();
        }
        
        if (evento.type == sf::Event::KeyPressed && !fimDeJogo) {
            switch (evento.key.code) {
                case sf::Keyboard::Up: cobra.mudarDirecao(Direcao::CIMA); break;
                case sf::Keyboard::Down: cobra.mudarDirecao(Direcao::BAIXO); break;
                case sf::Keyboard::Right: cobra.mudarDirecao(Direcao::DIREITA); break;
                case sf::Keyboard::Left: cobra.mudarDirecao(Direcao::ESQUERDA); break;
            }
        }
    }
}

void Game::atualizar() {
    if (fimDeJogo) return;
    
    if (relogio.getElapsedTime().asSeconds() >= tempoPorMovimento) {
        cobra.mover();
        relogio.restart();
        
        // Verifica colisões
        if (cobra.colisaoComParede(janela.getSize().x, janela.getSize().y) || 
            cobra.colisaoComProprioCorpo()) {
            fimDeJogo = true;
            return;
        }
        
        // Verifica colisão com comida
        if (cobra.colisaoComComida(comida)) {
            pontuacao++;
            cobra.crescer();
            gerarNovaComida();
        }
    }
}

void Game::desenhar() {
    janela.clear(sf::Color::Black);
    
    cobra.desenhar(janela);
    janela.draw(comida);
    
    textoPontuacao.setString("Pontos: " + std::to_string(pontuacao));
    janela.draw(textoPontuacao);
    
    if (fimDeJogo) {
        textoGameOver.setString("FIM DE JOGO!");
        sf::FloatRect bounds = textoGameOver.getGlobalBounds();
        textoGameOver.setOrigin(bounds.width / 2, bounds.height / 2);
        textoGameOver.setPosition(janela.getSize().x / 2.0f, janela.getSize().y / 2.0f);
        janela.draw(textoGameOver);
    }
    
    janela.display();
}

void Game::gerarNovaComida() {
    std::uniform_int_distribution<> distribX(0, (janela.getSize().x / 20) - 1);
    std::uniform_int_distribution<> distribY(0, (janela.getSize().y / 20) - 1);
    comida.setPosition(distribX(gen) * 20, distribY(gen) * 20);
}