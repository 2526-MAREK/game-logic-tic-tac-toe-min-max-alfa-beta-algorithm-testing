#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

#define BOARD_SIZE 5

int board_size = 5;
int row_win = 5;
int max_depth = 3; 
/*char board[BOARD_SIZE][BOARD_SIZE] ={{'-','-','-','-','-','-','-','-','-','-'},  // 10x10 max_depth = 2
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'},
                                    {'-','-','-','-','-','-','-','-','-','-'}}; */
char board[BOARD_SIZE][BOARD_SIZE] ={{'-','-','-','-','-'}, //509.674s one call algorithm min_max with alfa beta XD, and 134'205'625 possibilities :O this algorithm dont good for 5x5 tic tac tou for max_depth = 5 
                                    {'-','-','-','-','-'}, // 5x5 max_depth = 3
                                    {'-','-','-','-','-'},
                                    {'-','-','-','-','-'},
                                    {'-','-','-','-','-'}}; 
/*char board[BOARD_SIZE][BOARD_SIZE] ={{'-','-','-','-'}, // 4x4 max_depth = 3
                                    {'-','-','-','-'},
                                    {'-','-','-','-'},
                                    {'-','-','-','-'}};                                     */
/*char board[BOARD_SIZE][BOARD_SIZE] ={{'-','-','-'}, //3x3 max_depth = 5 //maximum recusion depth level, balances efficiency and AI predictions
                                       {'-','-','-'},
                                       {'-','-','-'}}; */                                                                        


/*Checks the horizontal axis to see if there is a winner*/
bool check_vertical(char symbol)
{
    int line;
    for(int j = 0;j<board_size;++j)
    {
        line = 0;
        for(int i =0; i<board_size;++i)
        {
            if(board[i][j] == symbol)                
                line +=1;
            else if(board[i][j] != symbol)  
                line = 0;
            else if((line == 0) &&((board_size - i)<row_win) )                             
                break;
            if( line >= row_win)
                return true;                
        }
    }
    return false;
}

/*Checks the vertical axis to see if there is a winner*/
bool check_horizontal(char symbol)
{
    int line;
    for(int i = 0;i<board_size;++i)
    {
        line = 0;
        for(int j =0; j<board_size;++j)
        {
            if(board[i][j] == symbol)                
                line +=1;
            else if(board[i][j] != symbol)  
                line = 0;
            else if((line == 0) &&((board_size - j)<row_win) )                             
                break;
            if( line >= row_win)
                return true;                
        }
    }
    return false;    
}

/*Checks the diagonal axis to see if there is a winner*/
bool check_diagonal(char symbol)
{
    std::vector<char> win;

    for(int i =0;i<row_win;++i)
        win.push_back(symbol);

    
    for(int i=0; i< board_size-row_win+1 ;++i)        
    {
        int temp  = 0;
        std::vector<char> diagonal;
        int x =i;
        int y = 0;
        for(int j=0;j<(board_size-i);++j){
            diagonal.push_back(board[x][y]);
            x += 1;
            y += 1;
        }
        for(int j =0;j<(diagonal.size()-win.size()+1);++j)            
        {
            //compare two vectors
            temp = 0;                
            for(int g=j,d = 0;g<row_win+j;++g,++d)
            {
                //std::cout<<"g: "<<g<<std::endl;
                //std::cout<<"d: "<<d<<std::endl;
                //clearstd::cout<<win[d]<<diagonal[g]<<std::endl;
                if(win[d] == diagonal[g])
                    ++temp;
            }     
            if(temp == row_win)         
                return true;
            /*std::cout<<"win size: "<<win.size()<<"diagonal size: "<<diagonal.size()<<std::endl;                
             if(win == diagonal)                
                return true;                */
        }
        //std::cout<<"ELO1"<<std::endl;
        temp = 0;
        x =0;
        y = i;
        for(int j=0;j<(board_size-i);++j){
            diagonal.push_back(board[x][y]);
            x += 1;
            y += 1;
        }
        for(int j =0;j<(diagonal.size()-win.size()+1);++j)            
        {
            //compare two vectors

            temp = 0; 
            for(int g=j,d = 0;g<row_win+j;++g,++d)
            {
                //std::cout<<"g: "<<g<<std::endl;
                //std::cout<<"d: "<<d<<std::endl;
                //std::cout<<"j: "<<j<<std::endl;
                //std::cout<<win[d]<<diagonal[g]<<std::endl;
                if(win[d] == diagonal[g])
                    ++temp;                  
            }     
            if(temp== row_win)         
                return true;
            /*    std::cout<<"win size: "<<win.size()<<"diagonal size: "<<diagonal.size()<<std::endl;                
            if(win == diagonal)                
                return true;*/
        }

        //std::cout<<"ELO2"<<std::endl;

        temp = 0;
        x =board_size -1 - i;
        y = 0;
        for(int j=0;j<(board_size-i);++j){
            diagonal.push_back(board[x][y]);
            x -= 1;
            y += 1;
        }
        for(int j =0;j<(diagonal.size()-win.size()+1);++j)            
        {
            //compare two vectors

            temp = 0; 
            for(int g=j,d = 0;g<row_win+j;++g,++d)
            {
                //std::cout<<"g: "<<g<<std::endl;
                //std::cout<<"d: "<<d<<std::endl;
               // std::cout<<"j: "<<j<<std::endl;
                //std::cout<<win[d]<<diagonal[g]<<std::endl;
                if(win[d] == diagonal[g])
                    ++temp;                  
            }     
            if(temp== row_win)         
                return true;
              /*  std::cout<<"win size: "<<win.size()<<"diagonal size: "<<diagonal.size()<<std::endl;                
            if(win == diagonal)                
                return true;                */
        }
        //std::cout<<"ELO3"<<std::endl;
        temp = 0;
        x =board_size -1;
        y = 0 + i;
        for(int j=0;j<(board_size-i);++j){
            diagonal.push_back(board[x][y]);
            x -= 1;
            y += 1;
        }
        for(int j =0;j<(diagonal.size()-win.size()+1);++j)            
        {
            //compare two vectors

            temp = 0; 
            for(int g=j,d = 0;g<row_win+j;++g,++d)
            {
                //std::cout<<"g: "<<g<<std::endl;
                //std::cout<<"d: "<<d<<std::endl;
                //std::cout<<"j: "<<j<<std::endl;
                //std::cout<<win[d]<<diagonal[g]<<std::endl;
                if(win[d] == diagonal[g])
                    ++temp;                  
            }     
            if(temp== row_win)         
                return true;
              /*  std::cout<<"win size: "<<win.size()<<"diagonal size: "<<diagonal.size()<<std::endl;                
             if(win == diagonal)                
                return true;                */
        }

        //std::cout<<"ELO4"<<std::endl;
    }
    return false;
}

/*check if there is a winner on the current board*/
bool check_win(char symbol)
{
return check_horizontal(symbol) || check_diagonal(symbol) || check_vertical(symbol);
}

// Simple function for checking if all places on the board are occupaied Returns True or False
bool check_if_game_finish()
{
    for(int y = 0;y<board_size;++y)
    {
        for(int x = 0;x<board_size;++x)
        {
            if(board[x][y] == '-')
                return false;
        }
    }
    return true;
}

int calculate_score()
{
    int size = board_size;
    int score =0;
    int temp;
    for(int i =0;i<size;++i)
    {
        temp = 0; 
        for(int j =0;j<size;++j)
        {
            if(board[i][j] == 'o')
                temp += 1;
            else if (board[i][j] == '-')                
            {
                temp = 0;
                break;
            }
        }
        if(temp != 0)
        {
            score += 10^temp;
        }
    }

    for(int i =0;i<size;++i)
    {
        temp = 0;
        for(int j =0;j<size;++j)
        {
            if(board[j][i] == 'o')
                temp += 1;
            else if (board[j][i] == '-')                
            {
                temp = 0;
                break;
            }
        }
        if(temp != 0)
        {
            score += 10^temp;
        }
    }

    temp = 0;

    for(int i =0;i<size;++i)
    {
        int temp = 0;
        for(int j =0;j<size;++j)
        {
            if(board[i][i] == 'o')
                temp += 1;
            else if (board[i][i] == '-')                
            {
                temp = 0;
                break;
            }
        }
        if(temp != 0)
        {
            score += 10^temp;
        }
    }

    temp = 0;

    for(int i =0;i<size;++i)
    {
        int temp = 0;
        for(int j =0;j<size;++j)
        {
            if(board[size- i][i - 1] == 'o')
                temp += 1;
            if (board[size - i][i - 1] == '-')                
            {
                temp = 0;
                break;
            }
        }
        if(temp != 0)
        {
            score += 10^temp;
        }
    }
    return score;
}

int inf = 900000000;

int number_of_calls_min_max_algorithm = 0;
/*min max alfa beta algorithm*/
int min_max_alfa_beta(char symbol, int depth,int a, int b)
{
    ++number_of_calls_min_max_algorithm;
    if(check_win(symbol)){
        if(symbol == 'o')
            return 10^8;
        else
            return (-1) * (10^8);
    }        

    if(check_if_game_finish() || depth == 0){
        if(symbol == 'o')
            return calculate_score();
        else    
            return (-1) * calculate_score();            
    }  

    int best_score;
    if(symbol == 'x'){
        symbol = 'o';
        best_score = (-1) * inf;
    }
    else{
        symbol = 'x';
        best_score = inf;
    }

    int temp;
    for(int i = 0; i< board_size ; ++i)
    {
        for(int j = 0; j<board_size;++j)
        {
            if(board[i][j] == '-')
            {
                if(symbol == 'o'){
                    board[i][j] = symbol;
                    temp = min_max_alfa_beta(symbol, depth -1,a,b);
                    if(best_score < temp)
                        best_score = temp;
                    if(a < best_score)     
                        a = best_score;
                    board[i][j] = '-';                                                                   
                    if(a>=b)
                        return best_score;
                }   
                else{
                    board[i][j] = symbol;
                    temp = min_max_alfa_beta(symbol, depth -1,a,b);
                    if(best_score > temp)
                        best_score = temp;
                    if(a > best_score)     
                        a = best_score;
                    board[i][j] = '-';                                                                   
                    if(a>=b)
                        return best_score;
                }                 
            }            
        }
    }
    return best_score;
}

void best_move()
{
    int best_score = (-1) * inf;
    int temp;
    int mov_i;
    int mov_j;
    for(int i = 0;i<board_size;++i)
    {
        for(int j = 0; j<board_size;++j)
        {
            if(board[i][j] == '-')
            {
                board[i][j] = 'o';
                temp = min_max_alfa_beta('o', max_depth, (-1)*inf, inf) ;
                board[i][j] = '-';      
                if(temp > best_score)             
                {
                    best_score = temp;
                    mov_i = i;
                    mov_j = j;
                }
            }
        }
    }
    board[mov_i][mov_j] = 'o';
}

void show_board_on_std_output()
{
    for(int i = 0;i<board_size;++i)
    {
        for(int j = 0; j<board_size;++j)
        {
            std::cout<<board[i][j];
        }
        std::cout<<std::endl;
    }              
}

void check_winner_game()
{
    if(check_win('o'))
        std::cout<<"winner is o"<<std::endl;

    if(check_win('x'))
        std::cout<<"winner is x"<<std::endl;        
}

void check_draw()
{
    if(check_if_game_finish())
        std::cout<<"draw"<<std::endl;    
}

void introduce_x_to_board()
{
    int temp_i;
    int temp_j;

    std::cout<<"i:";
    std::cin>>temp_i;
    std::cout<<"j:";
    std::cin>>temp_j;
    board[temp_i][temp_j] = 'x';
}
int main()
{
     //std::cout<<calculate_score()<<std::endl
    auto start = std::chrono::high_resolution_clock::now();
    best_move();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);   
    std::cout<<duration.count()/1000.0<<std::endl;
     check_winner_game();
    check_draw();
    show_board_on_std_output();  
    //std::cout<<check_win('o')<<std::endl;
    //std::cout<<check_horizontal('o')<<std::endl;
    //std::cout<<check_diagonal('o')<<std::endl;
    //std::cout<<check_vertical('o')<<std::endl;
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();
    

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();
    

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();
    

    best_move();
    show_board_on_std_output();  
    check_winner_game();
    check_draw();
    std::cout<<"number of calls min max algorithm: "<<number_of_calls_min_max_algorithm<<std::endl;
    introduce_x_to_board();
    show_board_on_std_output();
    check_winner_game();
    check_draw();
    

    //std::cout<<calculate_score()<<std::endl;
    return 0;
}



