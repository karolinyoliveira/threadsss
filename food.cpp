#include "food.h"

vector<pair<int,int> > foods;
pair<int,int> make_food(){
    return { rand()%(LINES-2)+1 , rand()%(COLS-2)+1 };
}


void init_food(){
    foods.clear();
    for(int i=0;i<FOOD_COUNT;i++){
        foods.push_back(make_food());
    }
}

void paint_food(){
    for(int i=0;i<foods.size();i++){
        move(foods[i].first,foods[i].second);
        init_pair(3,COLOR_RED,COLOR_BLACK);
        attron(COLOR_PAIR(3));
        addch('o');
        attroff(COLOR_PAIR(3));
    }
}

// TODO: SEMAPHORES IMPLEMENTATION
bool try_eating_food(pair<int,int> head){
    for(int i=0;i<foods.size();i++){
        if(foods[i].first==head.first && foods[i].second==head.second){
            foods.erase(foods.begin()+i);
            foods.push_back(make_food());
            return true;
        }
    }
    return false;
}