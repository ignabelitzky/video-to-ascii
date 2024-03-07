#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "menu.h"
#include "defs.h"

int main() {
    WINDOW *menuWindow = nullptr;
    WINDOW *playerWindow = nullptr;

    initscr();
    curs_set(0);    // This hides the cursor

    if(has_colors() != FALSE) {
        start_color();
        init_pair(2, COLOR_BLACK, COLOR_BLUE);
        attron(A_BOLD);
    }
    refresh();

    int height, width;
    getmaxyx(stdscr, height, width);
    

    if((menuWindow = newwin(height, width/4, 0, width - (width/4))) == nullptr) {
        endwin();   
        std::cerr << "Error creating the menu window." << std::endl;
        return 1;
    }
    if((playerWindow = newwin(height, width - (width/4), 0, 0)) == nullptr) {
        delwin(menuWindow);
        endwin();
        std::cerr << "Error creating the player window." << std::endl;
        return 1;
    }

    int key = 0, menuItem = 0;
    char option = '\0';
    bool quit = false;
    while(!quit) {
        draw_menu(menuWindow, menuItem);
        keypad(menuWindow, TRUE);
        noecho();
        do {
            key = wgetch(menuWindow);
            switch(key) {
            case KEY_DOWN:
                menuItem++;
                if(menuItem > MENUMAX-1)
                    menuItem = 0;
                break;
            case KEY_UP:
                menuItem--;
                if(menuItem < 0)
                    menuItem = MENUMAX-1;
                break;
            case 'q':
                endwin();
                return 0;
            default:
                break;
            } 
            draw_menu(menuWindow, menuItem);
        } while(key != '\n');

        //std::string density = " :-=+*#%@";
        std::string density = " ^l!i>~_[}1(|trxncJQ0Zwho#8@";
        //std::string density = "@8#ohwZ0QJcnxrt|(1}[_~>i!l^ ";

        cv::VideoCapture cap;
        cv::Mat frame;
        int videoHeight = 0, videoWidth = 0;
        int colorBlue = 0, colorGreen = 0, colorRed = 0;
        size_t index = 0, avgColor = 0;

        switch(menuItem) {
        case 0:
            cap.open("resources/encanto.mp4");    
            break;
        case 1:
            cap.open("resources/matrix.mp4");
            break;
        case 2:
            cap.open("resources/quantum.mp4");
            break;
        case 3:
            cap.open("resources/interstellar.mp4");
            break;
        case 4:
            cap.open("resources/pirates.mp4");
            break;
        case 5:
            cap.open("resources/inception.mp4");
            break;
        case 6:
            cap.open("resources/speed.mp4");
            break; 
        default:
            break;
        }

        wmove(playerWindow, 0, 0);
        bool once = false;
        int playerWindowHeight, playerWindowWidth;
        getmaxyx(playerWindow, playerWindowHeight, playerWindowWidth);
        for(;;) {
            cap >> frame;
            if(frame.empty()) {
                wclear(playerWindow);
                waddstr(playerWindow, "End of the video\n");
                waddstr(playerWindow, "Please exit or select another video.\n");
                wrefresh(playerWindow);
                break;
            }
            cv::resize(frame, frame, cv::Size(playerWindowWidth, playerWindowHeight-1));
            cv::Size sz = frame.size();
            videoWidth = sz.width;
            videoHeight = sz.height;
            for(int i = 0; i < videoHeight; ++i) {
                for(int j = 0; j < videoWidth; ++j) {
                    colorBlue = frame.at<cv::Vec3b>(i, j)[0];
                    colorGreen = frame.at<cv::Vec3b>(i, j)[1];
                    colorRed = frame.at<cv::Vec3b>(i, j)[2];
                    avgColor = (colorBlue + colorGreen + colorRed) / 3;
                    index = floor(avgColor / (255 / density.size()));
                    if(index >= density.size())
                        index = density.size() - 1;
                    addch(density.at(index));
                    index = 0;
                }
                move(i+1, 0);
            }
            if(!once) {
                wclear(menuWindow);
                draw_menu(menuWindow, menuItem);
                once = true;
            }
            refresh();
            napms(33);

            nodelay(menuWindow, true);
            option = wgetch(menuWindow);
            nodelay(menuWindow, false);
 
            if(option == 'q' || option == 'Q') {
                quit = true;
                option = '\0';
                cap.release();
                break;
            } else if(option == 'm' || option == 'M') {
                wclear(stdscr);
                refresh();
                draw_menu(menuWindow, menuItem);
                option = '\0';
                cap.release();
                break;
            }
        }
        echo();
    }
    delwin(menuWindow);
    delwin(playerWindow);
    endwin();

    return 0;
}
