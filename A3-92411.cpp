#include "rsdl.hpp" 
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;
#define coin_input_file  "coin_pattern.txt"
#define prob_input_file "probability.txt"
#define first_rocket_change_time 201
#define second_rocket_change_time 268
#define last_rocket_time 550
#define font_size 30
#define highscore_file "highscore.txt"
#define n_z 11
#define window_width 800
#define window_height 400
window win(window_width,window_height);
struct CoinFuncRetVal {
    int s;
    int time;
    vector<int> height_c;
    vector<vector<char> >input_shape;
    vector<vector<int> >start_point;
    vector<vector<bool> >catch_flag;

};
struct  rocket_ret {
     bool death;
     int time;
 };

 string IntToString (int a){
    ostringstream temp;
    temp<<a;
    return temp.str();
    }
vector<string> read_file(string input){
    string line;
    vector<string> text_content;
    ifstream myfile (input.c_str());
    if(!myfile){
}


    else
    {
        while ( getline (myfile,line) )
        {
          text_content.push_back(line);
        }
        myfile.close();
        
    }
    return text_content;
      
}
int read_highscore() {
    ifstream fin(highscore_file);
    string s;
    int tmp;
    if(getline(fin,s)){
           istringstream sin(s);
            sin>>tmp;
           
    }
    else
        tmp=0;
    return tmp;
}


double rand_maker() {
    srand(clock());
    int b=rand()%100;
    double a=(double)1/(b);
    return a;

}


bool draw_zapper(int z_shape,int xz,int yz,int y){
    bool death=0;
    srand(clock());
    switch(z_shape){
        case 0: {
            win.draw_png(string("horizontal1.png"), xz, yz,186,105);
            if(yz<=y+50 && y<=105+yz && xz<=240 && 240<=xz+186)
                death=1;
            break;
        }
        case 1: {
            win.draw_png(string("horizontal2.png"), xz, yz,271,99);
            if(yz<=y+50 && y<=99+yz && xz<=240 && 240<=xz+271)
                death=1;
            break;
        }
        case 2: {
            win.draw_png(string("horizontal3.png"), xz, yz,357,100);
            if(yz<=y+50 && y<=yz+100 && xz<=240 && 240<=xz+357)
                death=1;
            break;
        }
        case 3: {
            win.draw_png(string("left-right1.png"), xz, yz,154,152);
            if(yz<=y+50 && y<=yz+152 && xz<=240 && 240<=xz+154 && y+50>=240+yz-xz-20 && y<=240+yz-xz+10)
                death=1;
            break;
        }
        case 4: {

            win.draw_png(string("left-right2.png"), xz, yz,218,219);

            if(yz<=y+50 && y<=yz+219 && xz<=240 && 240<=xz+218 && y+50>=240+yz-xz-20 && y<=240+yz-xz+10)
                death=1;
            break;
        }
        case 5: {
            win.draw_png(string("left-right3.png"), xz, yz,276,279);
            if(yz<=y+50 && y<=yz+279 && xz<=240 && 240<=xz+276 && y+50>=240+yz-xz-20 && y<=240+yz-xz+10)
                death=1;
            break;
        }
        case 6: {
            win.draw_png(string("right-left1.png"), xz, yz,150,152);
            if(240>=xz && 240<=xz+150 && y<=yz+152 && y+50>=yz && y+50>=-240+yz+xz+150 && y<=-240+yz+xz+150+10)
                death=1;
            break;
        }
        case 7: {
            win.draw_png(string("right-left2.png"), xz, yz,216,218);
            if(240>=xz && 240<=xz+216 && y<=yz+218 && y+50>=yz && y+50>=-240+yz+xz+218-20 && y<=-240+yz+xz+218+10)
                death=1;
            break;
        }
        case 8: {
            win.draw_png(string("right-left3.png"), xz, yz,280,280);
            if(240>=xz && 240<=xz+280 && y<=yz+280 && y+50>=yz && y+50>=-240+yz+xz+280-20 && y<=-240+yz+xz+280+10)
                death=1;
            break;
        }
        case 9: {
            win.draw_png(string("vertical1.png"), xz, yz,101,184);
            if(y<=yz+184 && 240>=xz && 240<=xz+101 && y+50>=yz)
                death=1;
            break;
        }
        case 10: {
            win.draw_png(string("vertical2.png"), xz, yz,100,272);
            if(y+50>=yz && y<=yz+272 && 240<=xz+100 && 240>=xz)
                death=1;

            break;
        }
        case 11: {
            win.draw_png(string("vertical3.png"), xz, yz,70,260);
            if(y+50>=yz && y<=yz+260 && 240<=xz+70 && 240>=xz)
                death=1;
            break;
        }

    }
    return death;
}
void show_score(int coin,int score){
    win.show_text(IntToString(score), 1,1, WHITE,"New Athletic Font.ttf" , font_size);
    win.show_text(IntToString(coin), 1,31, WHITE,"New Athletic Font.ttf" , font_size);

}



void coin_draw(int x0,int y0,int x_jack,int y_jack,CoinFuncRetVal &jack) {
    vector<vector<char> > in=jack.input_shape;
    int row=in.size();
    int col=in[0].size();
    int start;
    int x=0;
    int sgn=0;
    int t=jack.time;
    

    for(int i=0;i<row;i++){


        for(int j=0;j<col;j++){
        
            if(in[i][j]=='0') {
                if(x0+40*j<=x_jack && x_jack<=x0+40*j+40 && y0+40*i-84<=y_jack && y_jack<=y0+40*i+40 && jack.catch_flag[i][j]==0)
                {   
                    jack.s ++;
                   jack.catch_flag[i][j]=1;

                }
                if(jack.catch_flag[i][j]==0) {
                    if(t==0) {
                    srand(clock());
                    start=rand()%7;}
                else if(t>0) {start=jack.start_point[i][j]+1; start=start%7;}
                    switch (start) {
                        case 0: {  win.draw_png(string("Coin01.png"), x0 +40*j, y0 +40*i,40,40);
                        break;

                            }
                        case 1: {  
                                win.draw_png(string("Coin11.png"), x0 +40*j, y0 +40*i,40,40);

                                break;

                            }
                        case 2: { 
                                win.draw_png(string("Coin21.png"), x0 +40*j, y0 +40*i,40,40);

                                break;
                            }
                        case 3: { 
                                win.draw_png(string("Coin31.png"), x0 +40*j, y0 +40*i,40,40);

                                break;
                            }
                        case 4: { 
                               win.draw_png(string("Coin41.png"), x0 +40*j,y0 +40*i,40,40);

                               break;
                            }
                        case 5: { 
                           
                               win.draw_png(string("Coin51.png"), x0 +40*j, y0 +40*i,40,40);

                               break;
                            }
                        case 6: { 
                           
                               win.draw_png(string("Coin61.png"), x0 +40*j, y0 +40*i,40,40);
                               break;

                            }
                        default: {
                            break ;
                            }
                }
                    jack.start_point[i][j]=start;        

                   }
               }   
                

        }
    }
    jack.time++;


 }

void rocket(int firsty,int secondy,rocket_ret &jack,int current_y) {

    jack.death=0;

    if(jack.time<=first_rocket_change_time-1) {
    
        win.draw_png(string("rocket warning.png"), 725, firsty,72,71);
    }
    if(jack.time>=first_rocket_change_time && jack.time<=second_rocket_change_time-1) {
        win.draw_png(string("rocket warning almost.png"), 697, secondy,100,100);


    }
    if(jack.time>=second_rocket_change_time) {
        win.draw_png(string("rocket.png"), window_width-3*(jack.time-second_rocket_change_time), secondy,498,139);
        if(window_width-3*(jack.time-268)<=240 && 240<window_width-3*(jack.time-268)+6 &&  secondy>=current_y && secondy<=current_y+3){
        jack.death=1;
}
    }
    jack.time++;

    }
double prob(double Plimit,double Pstart,int d,int v){
    double p=Pstart+(double)2/3.14 *(Plimit- Pstart)*atan(d/(9*v));
    return p;
}

vector<vector<vector<char> > >coin_data_extractor(){
   
    vector<char> temp;
    vector<vector<char> >shape;
    int num;
    string name;
    int row;
    int col;
    char c;
    int cc=0;
    int num_of_lines;
    string str;
    vector<vector<vector<char> > > data;
    ifstream fin1(coin_input_file);
    while(getline(fin1,str))
    num_of_lines++;
    ifstream fin(coin_input_file);
    fin>>num;
    for(int a=1;a<=num;a++){
        fin>>name>>row>>col;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                fin>>c;
                temp.push_back(c);
            }
            shape.push_back(temp);
            temp.clear();
        }
    data.push_back(shape);
    shape.clear();
    }
    return data;
}

vector<vector<char> > choose_coin_shape(vector<vector<vector<char> > > input){
    vector<vector<char> >out;
    srand(clock());
    int a=rand()%input.size();
    out=input[a];
    return out;

}
void update_highscore(int highscore){
    ofstream myfile;
    myfile.open (highscore_file);
    myfile <<IntToString(highscore);
    myfile.close();


}

int show_logo(){
    win.draw_bg("en3.png", 0, 0);
    win.draw_png(string("Logo.png"), 0, 0, 800,400);
    int highscore=read_highscore();
    win.show_text(IntToString(highscore),620,290, WHITE,"New Athletic Font.ttf" , 30);
    return highscore;
}

int main(){
    int Dp1,Dp2,Dp3;
    int x_co =0;
    int np1=0;
    int np2=0;
    int np3=0;
    int d1,d2,d3;
    int second_y;
    int D1_off,D2_off,D3_off;
    double Pstart1,Pstart2,Pstart3,Plimit1,Plimit2,Plimit3;
    int Y = 280;
    int total_score=0;
    vector<int> zap_jack;
    int vY = 0;
    int rocket_flag=0;
    rocket_ret jack4;
    int d=0;
    vector<int> x_coin;
    vector<int> x_z;
    vector<vector<int> >in;
    int total_c=0;
    vector<int> coin_height;
    vector<CoinFuncRetVal> jack;
    int n_c=0;
    int first_y;
    vector<vector<char> >in2;
    string str1,str2,str3;
    int x=0;
    int sgn=1;
    int n=0;
    int start_flag=0;
    vector<bool>temp2;
    vector<int>zapper_shape;
    vector<int>zapper_height;
    vector<int>temp3;
    vector<vector<bool> >initial_catch_flag;
    vector<vector<int> >start_point2;


    ifstream file(prob_input_file);
    file >> str1 >> Pstart1>>Plimit1>>Dp1>>D1_off;
    file >> str2 >> Pstart2>>Plimit2>>Dp2>>D2_off;
    file >> str3 >> Pstart3>>Plimit3>>Dp3>>D3_off; 


    int highscore=show_logo();    



    while(true){
        
            
        HANDLE({
            QUIT({return 0;})
            KEY_PRESS(q, {return 0;})
            /////click ru start?
            KEY_PRESS(SPACE, {
            start_flag=1;
               

            })
            LCLICK({ if(mouse_x>=380 && mouse_x<=460 && mouse_y>=290 && mouse_y<=330)
                start_flag=1;})

        })
        if(start_flag==1){



            int i=0;
                
                while(true){


                 win.draw_bg("en3.png", 0, 0);
                 win.draw_png(string("running2.png"),i, 280,77,85);
                 i=i+60;
                 if (i==240)
                    break;
                 win.update_screen();
                 DELAY(500);
             }
             DELAY(500);



        while(true) {
            win.draw_bg("back.png", x, 0);
            x += 5*sgn;
            if(x == 700)
            {
                x=0;
                n++;
            }

            vY += 1;
            Y += vY;
            if(Y < 0){
                    vY = 0;
                    Y = 0;
            }
            if(Y >280){
                    vY = 0;
                    Y = 281;
                    win.draw_png(string("running.png"), 240, 280,77,85);
            }
            if (Y>=0 && Y<=280){
                win.draw_bg("back.png", x, 0);
                if(Y<=239){
                win.draw_png(string("jetpack_bottom.png"), 240-12, 280+41,89,41);
                win.draw_png(string("jetpack_middle.png"), 240, Y+85,64,280-Y-41);
                }
                        win.draw_png(string("jumping.png"), 240, Y,77,85);
            }
                //////////////////prob
                d=700*n+x;
                d1=700*n+x-np1*Dp1;
                d2=700*n+x-np2*Dp2;
                d3=700*n+x-np3*Dp3;
                if (d1>=Dp1){
                    np1++;
                    double a=rand_maker();
                    double p=prob(Plimit1,Pstart1,d,5);
                    if(a<=p )
                    {
                        CoinFuncRetVal jack3;
                        jack3.s=total_c;
                        jack3.time=0;
                        x_coin.push_back(0);
                        srand(clock());
                        coin_height.push_back(rand()%190);
                        in2=choose_coin_shape(coin_data_extractor());
                        for(int j=0;j<in2.size();j++)
                        {
                            for(int k=0;k<in2[j].size();k++)
                            {
                                temp2.push_back(0);
                                temp3.push_back(0);
                            }
                           initial_catch_flag.push_back(temp2);
                           start_point2.push_back(temp3);
                           temp2.clear();
                           temp3.clear();
                       }
                       jack3.catch_flag=initial_catch_flag;
                       initial_catch_flag.clear();
                       jack3.start_point=start_point2;
                       start_point2.clear();
                       jack3.input_shape=in2;
                       jack.push_back(jack3);
                    }

                }
                    if (d2>=Dp2  && rocket_flag==0)
                    {
                        np2++;
                        double a=rand_maker();
                        double p=prob(Plimit2,Pstart2,d,5);
                        if(a<=p)
                        {
                            jack4.death=0;
                            jack4.time=0;
                            rocket_flag=1;
                            first_y=Y;

                        }

                    }
                    if (d3>=Dp3)
                    {
                        np3++;
                        double a=rand_maker();
                        double p=prob(Plimit3,Pstart3,d,5);
                        if(a<=p )
                        {

                            zap_jack.push_back(1);
                            x_z.push_back(0);
                            srand(clock());
                            zapper_shape.push_back(rand()% n_z);
                            srand(clock());
                            zapper_height.push_back(rand()%170);


                        }

                    }

                    /////////////rocket offset
                    if (rocket_flag==1) {
                        rocket(first_y,second_y,jack4,Y);
                        if(jack4.death==1) {
                            if (total_score>highscore)
                                highscore=total_score;
                            update_highscore(highscore);
                            main();
                            return 0;
                        }
                        if(jack4.time==first_rocket_change_time)
                            second_y=Y;

                        if(jack4.time==last_rocket_time)
                            rocket_flag=0;
                    }
                int n=jack.size();
                for(int i=0;i<n;i++) {
                    coin_draw((x_coin[i] + D1_off),coin_height[i],240,Y,jack[i]);
                    x_coin[i] -=5*sgn;
                    total_c=jack[i].s;

                }
                for(int i=0;i<zap_jack.size();i++) {
                    
                    bool death2=0;
                    death2=draw_zapper(zapper_shape[i],x_z[i]+D3_off,zapper_height[i],Y);
                    if(death2==1) {
                        DELAY(1000);

                        if(total_score>highscore)
                            highscore=total_score;
                            update_highscore(highscore);
                        main();
                        return 0;
                    }
                    x_z[i] -=5*sgn;

                }
                total_score=d/100+2*total_c;
                show_score(total_c,total_score);
                HANDLE({
                QUIT({return 0;})
                KEY_PRESS(q, {return 0;})
                KEY_PRESS(SPACE, {
                    
                        vY -= 6;
                        if(vY <= -20)
                            vY = -20;

                    })
                      
                })

                win.update_screen();
                        DELAY(15);
              }

        }
        win.update_screen();
        DELAY(15);

        
    }

}

