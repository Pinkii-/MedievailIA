#include <SFML/Graphics.hpp>
#include "Utils/util.h"
#include "board.h"

#include <iostream>

const int TILE_SIZE = 30;
const float UISPACE = 15;

int WIDTH = sf::VideoMode::getFullscreenModes()[0].width;
int HEIGHT = sf::VideoMode::getFullscreenModes()[0].height-3*TILE_SIZE;

int ROWS = 50;
int COLS = 50;

bool GENERATE_MAP = true;

int main() {

	sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "MediavalIA",sf::Style::Close | sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    clock.restart();
    int fps = 20;
    float deltaDraw = 0;

    srand(time(0));

    Board board;
    board.init();
    window.clear();
    window.draw(board);
    window.display();

	while (window.isOpen()) {
        sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type)
            {
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Down:
					board.updateDirCamera(sf::Vector2f(0,1));
                    break;
                case sf::Keyboard::Up:
					board.updateDirCamera(sf::Vector2f(0,-1));
                    break;
                case sf::Keyboard::Right:
					board.updateDirCamera(sf::Vector2f(1,0));
                    break;
                case sf::Keyboard::Left:
					board.updateDirCamera(sf::Vector2f(-1,0));
                    break;
//                case sf::Keyboard::S:
//                    board.updateNpc(deltaTime,sf::Vector2f(0,1));
//                    break;
//                case sf::Keyboard::W:
//                    board.updateNpc(deltaTime,sf::Vector2f(0,-1));
//                    break;
//                case sf::Keyboard::D:
//                    board.updateNpc(deltaTime,sf::Vector2f(1,0));
//                    break;
//                case sf::Keyboard::A:
//                    board.updateNpc(deltaTime,sf::Vector2f(-1,0));
//                    break;
                case sf::Keyboard::Z:
                    deltaTime += 0.1;
                    break;
                case sf::Keyboard::X:
                    deltaTime -= 0.1;
                    if (deltaTime < 0) deltaTime = 0;
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        deltaDraw += deltaTime;
        board.update(deltaTime);
        if (deltaDraw >= 1.f/float(fps)) {
            board.updateD(deltaTime,deltaDraw);
			deltaDraw = 0;
            window.clear();
            window.draw(board);
            window.display();
        }
    }
    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////7

MS4wNDAzfHwxMzkxMDA2MzY1NDM4OzEzOTEwMDYzNjU0Mzg7MTM5MTA0MjMwODA4MnwwMDExMDAxMXwxNjUwMjEzMzQ4ODU5LjM0MTg7MzY3NzI3MjE1OTA1Ny42Nzg7MTU7NjsxNTszMTstMTstMTswOzA7MDswOzA7MDswOzY7MDswOzExOzI3fDExMCwxMTEsMjc1MjM3Njc0MywwOzEwMCwxMDEsMzI1NzY5NzUzMCwwOzgyLDgyLDcwMDUzNDgyLDA7NjgsNjgsMTE0NDA4MzI0LDA7NjAsNjAsMzQ5Njk0NjU5LDA7NTAsNTAsNjIzODUzNjM4LDA7NDYsNDYsMTg0Mjk4MDY1MCwwOzUwLDUwLDM2NTc4OTY1MTI4LDA7MzgsMzgsMjMwOTQyMDg4NTczLDA7MjQsMjQsNDAyNjM3MDUyNzA4LDA7fDQ1MDM1OTk2MjczNDU5MTk7MjUzMjg2MjQ3MzUzNTQ4NzsyMjUxODAwMDgyMDk4NjkxOzM5NDA2NTI0OTI1MzE3MTM7MjI1MTc5OTgxOTk3Njg0NzszMDAyMzUzOTM4NTk1ODQxOzU4NDExNTU1MjIyNXwzODY5Njk3OTIxMzkyNjM5OzIyNTIwNzQ5NTE5Mzk2NzU7NzQ3NTM%3D%21END%21

/////////////////////////////////////////////////////////////////////////////////////7

var interval = 250;
var autoBuy = true;
var autoBuyTxt = "on";
var keepForGolden = true;
var keepForGoldenTxt = "on";
var name;
var price;
var cpsItem;
var selected=0;
var currentCps=Game.cookiesPs;

document.addEventListener('keydown', function(event) {
    if(event.keyCode == 65) {
        autoBuy = !autoBuy;
        autoBuyTxt = autoBuy ? "on" : "off";
    }
    else if(event.keyCode == 71) {
        keepForGolden = !keepForGolden;
        keepForGoldenTxt = keepForGolden ? "on" : "off";
    }
});

function OptimalItem()
{
    var cpc = Number.MAX_VALUE;

    var sel;

    for(i = Game.UpgradesInStore.length-1; i >= 0; i--)
    {
        var cps1 = 0;
        var me = Game.UpgradesInStore[i];
        var x = Game.UpgradesInStore[i].id;
        if (x != 64 && x != 74 && x != 84 && x != 85)
        {
            Game.UpgradesById[x].toggle();
            Game.CalculateGains();
            for(j = Game.ObjectsById.length-1; j >= 0; j--){ cps1 += Game.ObjectsById[j].cps()*Game.ObjectsById[j].amount; }
            var cps2 = cps1 * Game.globalCpsMult;
            Game.UpgradesById[x].toggle();
            Game.CalculateGains();
            var myCps = cps2 - currentCps;
            var cpsUpgrade = me.basePrice *(Game.cookiesPs + myCps) / myCps;
            if (cpsUpgrade < cpc && myCps >= 0.1)
            {
                cpc = cpsUpgrade;
                sel = me;
                cpsItem = myCps;
                name = me.name;
                price = Math.round(me.basePrice);
            }
        }
    }

    for(i = Game.ObjectsById.length-1; i >= 0; i--){
        var cps1=0;
        var me = Game.ObjectsById[i];
        me.amount++;
        Game.CalculateGains();
        for(j = Game.ObjectsById.length-1; j >= 0; j--){ cps1 += Game.ObjectsById[j].cps()*Game.ObjectsById[j].amount;}
        var cps2 = cps1 * Game.globalCpsMult;
        me.amount--;
        Game.CalculateGains();
        var myCps = cps2 - currentCps;
        var cpsBuilding = me.price *(Game.cookiesPs + myCps) / myCps;
        if (cpsBuilding < cpc && myCps >= 0.1)
        {
            cpc = cpsBuilding;
            sel = me;
            cpsItem = myCps;
            name = me.name;
            price = Math.round(me.price);
        }
    }
    currentCps = Game.cookiesPs;
    selected=1;

    return sel;
}

function Display()
{
    var mult = 1;
    if (Game.frenzy>0) mult=Game.frenzyPower;

    var time;
    if(!keepForGolden){time = (price - Game.cookies) / Game.cookiesPs;}
    else if(Game.UpgradesById[86].bought) {time = 84000/mult + (price - Game.cookies) / Game.cookiesPs;}
    else {time = 12000/mult + (price - Game.cookies) / Game.cookiesPs;}
    time = time < 0 ? 0 : Beautify(time);

    var numb = (Math.abs(Game.computedMouseCps / Game.cookiesPs));
    numb = numb.toFixed(3);

    Game.Ticker = "Buying " + name + " for " + Beautify(price) + " at " + Beautify(Math.round(price / (cpsItem*Game.globalCpsMult))) + " cookies per CPS!" + "<br>This will take " + time + " seconds without manually clicking." + "<br>Each click would save you " + numb + " seconds." + "<br>Click A to toggle auto-buy. Auto-buy is currently " + autoBuyTxt + "<br>Click G to toggle the golden cookie maximisation. Maximisation is currently " + keepForGoldenTxt;
     Game.TickerAge = interval;
}

var cookieBot = setInterval(function () {
    var mult = 1;
    if (Game.frenzy>0) mult=Game.frenzyPower;

    if(autoBuy && selected==1 && !keepForGolden && Game.cookies >= price) {OptimalItem().buy(); selected=0;}
    else if(autoBuy && selected==1 && keepForGolden && Game.UpgradesById[86].bought && Game.cookies >= (price + Game.cookiesPs*84000/mult)) {OptimalItem().buy(); selected=0;}
    else if(autoBuy && selected==1 && keepForGolden && !Game.UpgradesById[86].bought && Game.cookies >= (price + Game.cookiesPs*12000/mult)) {OptimalItem().buy(); selected=0;}
    else if(selected==0 || currentCps!=Game.cookiesPs){OptimalItem();}
    Display();}, interval
);
*/
