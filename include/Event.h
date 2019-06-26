#pragma once

class Event {
  enum event {METEOR};
public:
  static void Meteor(int qtd = 1, int damage = -1);  // Infligir dano a 'qtd' entidades de ambos os lados
  static void Run();
//   void OverpowerMeteor(int target);  // Infligir dano aa carta de indice target
  static bool occured;
};