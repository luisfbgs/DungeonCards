#pragma once

class Event {
  enum event {
    METEOR = 0,
    REST,
    PLAYERS_REST,
    IMMUNE,
    VOLUNTEER    
  };
public:
  // Infligir dano a 'qtd' entidades aleatórias
  static void Meteor(int qtd = 1, int damage = 1);
  // Cura 3 hp de uma carta aleatória
  static void Rest();
  // Cura 1 hp de todos os jogadores
  static void PlayersRest();
  // Uma carta de jogador fica imune no próximo turno  
  static void Immune();
  // Um inimigo aleatório ataca uma carta ao lado
  static void Volunteer();

  static void Run();
  static void ChooseEvent(int whichEvent);
  static bool occured;
};