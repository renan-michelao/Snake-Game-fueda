// Cabeçalho do Jogo

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "snake.h"

class Game {
private:
    sf::RenderWindow& janela;
    Snake& cobra;
    sf::RectangleShape comida;
    sf::Clock relogio;
    float tempoPorMovimento;
    int pontuacao;
    bool fimDeJogo;
    
    // Elementos de UI
    sf::Text textoPontuacao;
    sf::Text textoGameOver;
    
public:
    Game(sf::RenderWindow& janela, Snake& cobra, const sf::Font& fonte);
    
    void processarEventos();
    void atualizar();
    void desenhar();
    void gerarNovaComida();
    
    // Getters
    bool isFimDeJogo() const { return fimDeJogo; }
    int getPontuacao() const { return pontuacao; }
};

#endif