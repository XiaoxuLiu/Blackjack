//
//  main.cpp
//  Black_Jack
//
//  Created by Xiaoxu Liu on 15/4/1.
//  Copyright (c) 2015年 Xiaoxu Liu. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

int current = 0;
const string Color_variety[4] = {"Spade", "Heart", "Club", "Diamond"};
const string Point_num[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K"};
const float Count[]={1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};

struct card
{
    string color;//The color of the cards
    string point;//The point of the cards
    float count;//The number every card represents
};

struct player
{
    struct card pk[11];//cards of a player
    float num;//total score
    int size;
};

//Initialization of cards
void card_initial(card poker[])
{
    for(int i=0;i<52;i++){
        poker[i].color=Color_variety[i/13];//Color
        poker[i].point=Point_num[i];//Points
        poker[i].count=Count[i];//Counts
    } 
}

//Initialization of player
void player_initial(player* computer,player* people)
{
    computer->num=0;//score
    computer->size=0;//number of score
    for(int i=0;i<11;i++){
        computer->pk[i].color="non";
        computer->pk[i].point='\0';
        computer->pk[i].count=0;
    }
    
    people->num=0;
    people->size=0;
    for(int i=0;i<11;i++){
        people->pk[i].color="non";
        people->pk[i].point='\0';
        people->pk[i].count=0;
    }
}


//Random shuffle
void shuffle(card poker[])
{
    srand(time(NULL));//random seeds
    int j,k;
    card temp;
    for(int i=0;i!=1000;i++)//exchange
    {
        j=rand();
        k=rand();
        temp=poker[j];
        poker[j]=poker[k];
        poker[k]=temp;
    }
}


//cards of a player
void show(player* people)
{
    for(int i=0;i<people->size;i++)
        cout<<people->pk[i].color<<people->pk[i].point<<" ";//color and point
}


//deal
void distribute(player* people,card poker[])
{
    int i=people->size;//give one of the players card
    people->pk[i].color=poker[current].color;
    people->pk[i].count=poker[current].count;
    people->pk[i].point=poker[current].point;
    people->num+=poker[current].count;//score changes
    people->size++;
    current++;//cards change
}


//player
void people_play(player* person,card poker[])
{
    cout<<"Your turn"<<endl;
    cout<<"You get card"<<" ";
    distribute(person,poker);//Player gets 2 cards first
    distribute(person,poker);
    show(person);
    char ch='y';
    while(ch=='y')
    {
        cout<<"\n";
        cout<<"Do you wanna one more card?(y/n)：";
        cin>>ch;
        while(ch!='y'&&ch!='n'&&ch!='Y'&&ch!='N')
        {
            cout<<"Sorry!You can only input y or n, please input again:";
            cin>>ch;
        }
        if(ch=='y'||ch=='Y'){
            cout<<"One more card：";
            distribute(person,poker);//give cards to player
            show(person); //show the cards now
        }
        if(person->num>21){
            cout<<"\n"<<"You lose!"<<endl;
            break;
        }
    }//player ends
}


//Computer
void computer_play(player* computer,player* person,card poker[])
{
    cout<<"Computer's turn"<<endl;
    cout<<"Computer gets card"<<" ";
    distribute(computer,poker);//Computer gets 2 cards first
    distribute(computer,poker);
    show(computer);
    while(computer->num<=person->num)
    {
        cout<<"\n"<<"One more card：";
        distribute(computer,poker);
        show(computer);
        if(computer->num==person->num&&computer->size>=person->size)
            break;
    }
    cout<<"\n";
    if(computer->num>21)
        cout<<"You win!"<<endl;
    else if(computer->num==person->num&&computer->size==person->size)
        cout<<"It ends in a draw!"<<endl;
    else cout<<"You lose!"<<endl;
}

//main function
int main()
{
    card poker[52];
    card_initial(poker);//initialize
    player computer,person;//define the players
    
    cout<<"----------Start!---------"<<endl;
    
    char Ch;
    do{
        shuffle(poker);
        player_initial(&computer,&person);
        people_play(&person,poker);
        if(person.num<=21)
            computer_play(&computer,&person,poker);
        
        cout<<"Continue?(y/n)：";
        cin>>Ch;
        while(Ch!='y'&&Ch!='n'&&Ch!='Y'&&Ch!='N')
        {
            cout<<"Sorry!You can only input y or n, please input again:";
            cin>>Ch;
        }
    }
    while(Ch=='y'||Ch=='Y');
    system("pause");
    return 0;
}