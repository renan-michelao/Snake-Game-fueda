// Cabeçalho da cobra

#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class Direcao { PARADO, CIMA, BAIXO, DIREITA, ESQUERDA };

class Snake {
private:
    std::vector<sf::RectangleShape> segmentos;
    Direcao direcaoAtual;
    int tamanhoBloco;

public:
    Snake(int tamanhoBloco, int posX, int posY);
    
    // Métodos de controle
    void mover();
    void crescer();
    void mudarDirecao(Direcao novaDirecao);
    
    // Métodos de consulta
    sf::Vector2f getPosicaoCabeca() const;
    bool colisaoComProprioCorpo() const;
    bool colisaoComParede(int larguraJanela, int alturaJanela) const;
    bool colisaoComComida(const sf::RectangleShape& comida) const;
    
    // Métodos de desenho
    void desenhar(sf::RenderWindow& janela) const;
    
    // Getters
    int getTamanho() const { return segmentos.size(); }
    Direcao getDirecao() const { return direcaoAtual; }
};

#endif