#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <string>

// --- Configurações Gerais do Jogo
const int LARGURA_JANELA = 800;
const int ALTURA_JANELA = 600;
const int TAMANHO_BLOCO = 20;

enum class Direcao{ PARADO, CIMA, BAIXO, DIREITA, ESQUERDA };

// Gerador de Números aleatórios
std::random_device rd;
std::mt19937 gen(rd());

int main(){
    sf::RenderWindow janela(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Snake Game");
    janela.setFramerateLimit(60);

    // --- CARREGANDO FONTES E CRIANDO TEXTOS ---
    sf::Font fonte;
    // carrega o arquivo de fonte
    if(!fonte.loadFromFile("./google-carlito-fonts/Carlito-Regular.ttf")){
        // Se falhar, imprime um erro no terminal
        // O programa ainda vai rodar, porém sem texto
        perror("Erro ao carregar fonte!");
    }

    // Texto para a pontuação
    sf::Text textoPontuacao;
    textoPontuacao.setFont(fonte);
    textoPontuacao.setCharacterSize(24); // Define o tamanho em pixels
    textoPontuacao.setFillColor(sf::Color::White);
    textoPontuacao.setPosition(10, 10); // Posição no canto superior esquerdo

    // Texto para GAME OVER
    sf::Text TextGameOver;
    TextGameOver.setFont(fonte);
    TextGameOver.setCharacterSize(50);
    TextGameOver.setFillColor(sf::Color::Red);

    // --- Criação dos Elementos do Jogo ---

    // A cobra começa com um único quadrado (a cabeça) no centro da tela
    // Usamos um 'vector' para armazenar as partes da cobra. Por enquanto só tem uma (a cabeça)
    std::vector<sf::RectangleShape> cobra; // array dinâmico
    sf::RectangleShape cabeca;
    cabeca.setSize(sf::Vector2f(TAMANHO_BLOCO, TAMANHO_BLOCO));
    cabeca.setFillColor(sf::Color::Green);
    cabeca.setPosition(LARGURA_JANELA / 2, ALTURA_JANELA / 2); // a cobra começa no centro da janela
    cobra.push_back(cabeca); // Adiciona a cabeça ao corpo da cobra (vetor), (como se fosse uma fila, adiciona atrás (no final))

    
    // A comida é um único quadrado vermelho em uma posição inicial (100, 100) x, y
    sf::RectangleShape comida;
    comida.setSize(sf::Vector2f(TAMANHO_BLOCO, TAMANHO_BLOCO));
    comida.setFillColor(sf::Color::Red);
    comida.setPosition(100, 100);


    // --- VARIÁVEIS DE CONTROLE DO JOGO
    Direcao direcaoAtual = Direcao::DIREITA; // A cobra começa se movimentando para a direta
    sf::Clock clock; // O relogio que controla a velocidade do jogo
    float tempoPorMovimento= 0.1f; // A cobra se moverá a cada 0.1 segundos
    int pontuacao = 0;
    bool fimDeJogo = false;

    // --- LOOP PRINCIPAL
    while(janela.isOpen()){
        // --- PROCESSAMENTO DE EVENTOS
        sf::Event evento;
        while(janela.pollEvent(evento)){
            if(evento.type == sf::Event::Closed){
                janela.close();
            }

            // Implementação dos controles do jogador
            // Vamos adicionar a verificação de tecla pressionada
            if(evento.type == sf::Event::KeyPressed){ // verifica se alguma tecla foi pressionada
            // verifica qual tecla foi pressionada
            if(evento.key.code == sf::Keyboard::Up && direcaoAtual != Direcao::BAIXO){
                // Para entrar no if, a condição a ser satisfeita é: A tecla pressionada não pode ser o oposto da direção atual da cobra
                direcaoAtual = Direcao::CIMA;
            }
            if(evento.key.code == sf::Keyboard::Down && direcaoAtual != Direcao::CIMA){
                direcaoAtual = Direcao::BAIXO;
            }
            if(evento.key.code == sf::Keyboard::Right && direcaoAtual != Direcao::ESQUERDA){
                direcaoAtual = Direcao::DIREITA;
            }
            if(evento.key.code == sf::Keyboard::Left && direcaoAtual != Direcao::DIREITA){
                direcaoAtual = Direcao::ESQUERDA;
            }
                
        }
        }

        

        // --- LÓGICA DO JOGO ---

        // --- MOVIMENTO DA COBRA ---
        if(!fimDeJogo){
            if(clock.getElapsedTime().asSeconds() >= tempoPorMovimento){
                // A lógica é mover o corpo de trás para frente
                // Começamos no último segmento e vamos até o segundo (índice 1)
                for(size_t i = cobra.size() - 1; i > 0; i--){
                    cobra[i].setPosition(cobra[i - 1].getPosition());
                }

                // Agora vamos mover a cabeça com base na direção
                if(direcaoAtual == Direcao::CIMA){
                    cobra[0].move(0, -TAMANHO_BLOCO);
                }
                if(direcaoAtual == Direcao::BAIXO){
                    cobra[0].move(0, +TAMANHO_BLOCO);
                }
                if(direcaoAtual == Direcao::DIREITA){
                    cobra[0].move(+TAMANHO_BLOCO, 0);
                }
                if(direcaoAtual == Direcao::ESQUERDA){
                    cobra[0].move(-TAMANHO_BLOCO, 0);
                }
                clock.restart();
            }

             // --- COLISÃO COM A PARADE ---     
            if(cobra[0].getPosition().x < 0 || cobra[0].getPosition().x >= LARGURA_JANELA || cobra[0].getPosition().y < 0 ||
             cobra[0].getPosition().y >= ALTURA_JANELA){
                fimDeJogo = true;
            }

            // Colisão com o próprio corpo
            for(size_t i = 1; i < cobra.size() - 1; i++){
                if(cobra[0].getGlobalBounds().intersects(cobra[i].getGlobalBounds())){
                    fimDeJogo = true;
                    break;
                }
            }

            // --- COLISÃO COM A COMIDA ---
            // Verificamos se a cabeça da cobra (cobra[0]) está tocando a comida
            if(cobra[0].getGlobalBounds().intersects(comida.getGlobalBounds())){
                std::cout << "mim comeu" << std::endl;
                /*
                    o comando cobra[0].getGlobalBound() é como se fosse um retângulo invisível que tem a posição e o tamanho exato da cabeça da cobra;
                    intersects(comida.getGlobalBounds()) está perguntando se o retângulo da cobra está cruzando (intersecção) com o 
                    retângulo da comida. Caso eles estiverem se tocando, a função retorna true, caso contrário retorna false
                */

                // 1. Vamos mover a comida para outro lugar aleatório
                // Para isso temos que calcular quantas posições de bloco existem na horizontal e na vertical
                std::uniform_int_distribution<> distribX(0, (LARGURA_JANELA / TAMANHO_BLOCO) - 1);
                std::uniform_int_distribution<> distribY(0 , (ALTURA_JANELA / TAMANHO_BLOCO) - 1);

                // Geramos uma nova posiçao e bloco e convertemos para pixels
                comida.setPosition(distribX(gen) * TAMANHO_BLOCO, distribY(gen) * TAMANHO_BLOCO);
                pontuacao++;

                // 2. Fazer a cobra crescer
                sf::RectangleShape novoSegmento;
                novoSegmento.setSize(sf::Vector2f(TAMANHO_BLOCO, TAMANHO_BLOCO));
                novoSegmento.setFillColor(sf::Color::Green);
                // Vamos adicionar o novoSegmento no lugar do último segmento atual (a cauda)
                novoSegmento.setPosition(cobra.back().getPosition()); // é um atalho para pegar a posição do último elemento do vector cobra
                cobra.push_back(novoSegmento);
            }

        
        }

        // --- DESENHO NA TELA --- 
        janela.clear(sf::Color::Black); // Limpa a tela com fundo preto

        // Desenha a cobra inteira (por enquanto só a cabeça)
        // Este é um loop for 'moderno'. Para cada segmento que existir dentro da lista cobra, execute o código
        for(const auto& segmento : cobra){
            janela.draw(segmento); // desenha o segmento (a cobra inteira)
            //std::cout << cobra.size() << std::endl;
        }

       // janela.draw(cabeca);
        janela.draw(comida);

        // Atualiza o texto da pontuação o desenha
        textoPontuacao.setString("Pontos: " + std::to_string(pontuacao));
        janela.draw(textoPontuacao);

        if(fimDeJogo){
            TextGameOver.setString("FIM DE JOGO!");
            //centraliza o texto na tela
            sf::FloatRect bounds = TextGameOver.getGlobalBounds();
            TextGameOver.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            TextGameOver.setPosition(LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f);
            janela.draw(TextGameOver);
        }
        
        janela.display(); // Mostra o resultado
    }

    return 0;
}