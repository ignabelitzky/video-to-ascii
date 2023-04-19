#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "menu.h"
#include "defs.h"

int main(int argc, char** argv) {
    WINDOW *menuWindow = nullptr;

    int key = 0, menuItem = 0;
    int width = 0, height = 0;
    bool quit = false;
    char option = '\0';

    initscr();
    curs_set(0);    // This hides the cursor

    if(has_colors() != FALSE) {
        start_color();
    }
    refresh();

    getmaxyx(stdscr, height, width);
    

    if((menuWindow = newwin(height, width/4, 0, width - (width/4))) == nullptr) {
        endwin();
        std::cerr << "Error creating the menu window." << std::endl;
        return 1;
    }

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

        std::string density = "!@#$%^&*()_+ ";

        cv::VideoCapture cap;
        cv::Mat frame;
        int videoHeight = 0, videoWidth = 0;
        int colorBlue = 0, colorGreen = 0, colorRed = 0;
        int index = 0, avgColor = 0;

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

        move(0, 0);
        bool once = false;
        for(;;) {
            cap >> frame;
            cv::Size sz = frame.size();
            videoWidth = sz.width;
            videoHeight = sz.height;
            if(frame.empty()) {
                std::cout << "Enf of the video" << std::endl;
                break;
            }
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
            napms(42);

            nodelay(menuWindow, true);
            option = wgetch(menuWindow);
            nodelay(menuWindow, false);
 
            if(option == 'q' || option == 'Q') {
                quit = true;
                option = '\0';
                break;
            } else if(option == 'm' || option == 'M') {
                wclear(stdscr);
                refresh();
                //wclear(menuWindow);
                draw_menu(menuWindow, menuItem);
                option = '\0';
                break;
            }
        }
        echo();
    }
    endwin();

    return 0;
}
