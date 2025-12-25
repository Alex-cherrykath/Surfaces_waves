
#include "test.h"
namespace nkentseu{
//ajouter les proprietes position de type vector2; avec une propriete gravity x=getwidht/2; de 9.81; R =100
    Count::Count(const ApplicationProperties& props) : Application(props) {
    }

    void Count::Setup(){
        position.x=GetWindowWidth()/2;
        position.y=100.0f;

    }

    void Count::Update(float deltaTime){
        position.y+= gravity*deltaTime*50;
        if(position.y>=GetWindowHeight()-R){
            position.y-= friction*deltaTime*80;
        }

    }

    void Count::Draw(){
       
        Fill(graphics::Color::Red);
        Circle(position,R);

    } //lire les notions de vecteurs, force. gravite. ressort, champs magnetiquesm toutes les lois de newton

    
   
}