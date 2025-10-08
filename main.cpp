#include <SFML/Graphics.hpp>
#include <iostream>
#include "snake.h"
#include "game.h"

const int LARGURA_JANELA = 800;
const int ALTURA_JANELA = 600;
const int TAMANHO_BLOCO = 20;

int main() {
    sf::RenderWindow janela(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Snake Game");
    janela.setFramerateLimit(60);
    
    // Carrega fonte
    sf::Font fonte;
    if (!fonte.loadFromFile("./google-carlito-fonts/Carlito-Regular.ttf")) {
        perror("Erro ao carregar fonte!");
        return -1;
    }
    
    // Cria a cobra no centro da tela
    Snake cobra(TAMANHO_BLOCO, LARGURA_JANELA / 2, ALTURA_JANELA / 2);
    
    // Cria o jogo
    Game jogo(janela, cobra, fonte);
    
    // Loop principal
    while (janela.isOpen()) {
        jogo.processarEventos();
        jogo.atualizar();
        jogo.desenhar();
    }
    
    return 0;
}