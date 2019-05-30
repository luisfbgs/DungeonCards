#ifndef ACTION
#define ACTION
enum ActionNames {
    MOVE
};
// Classe base para as acoes a serem executadas pelo tabuleiro
class Action {
public:
    static void Run(int idSource, int idDest);
private:
}; 

#endif