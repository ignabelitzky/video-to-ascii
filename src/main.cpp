#include <iostream>
#include <chrono>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "../include/menu.hpp"
#include "../include/defs.hpp"
#include "../include/audio.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "../include/miniaudio.hpp"

static void clear_window(WINDOW *playerWindow) {
    wclear(playerWindow);
    waddstr(playerWindow, "End of the video\n");
    waddstr(playerWindow, "Please exit or select another video.\n");
    wrefresh(playerWindow);
}

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
                delwin(menuWindow);
                delwin(playerWindow);
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
        std::string mp3Filepath = "";

        switch(menuItem) {
        case 0:
            cap.open("resources/encanto.mp4");
            mp3Filepath = "resources/encanto.mp3";
            break;
        case 1:
            cap.open("resources/matrix.mp4");
            mp3Filepath = "resources/matrix.mp3";
            break;
        case 2:
            cap.open("resources/quantum.mp4");
            mp3Filepath = "resources/quantum.mp3";
            break;
        case 3:
            cap.open("resources/interstellar.mp4");
            mp3Filepath = "resources/interstellar.mp3";
            break;
        case 4:
            cap.open("resources/pirates.mp4");
            mp3Filepath = "resources/pirates.mp3";
            break;
        case 5:
            cap.open("resources/inception.mp4");
            mp3Filepath = "resources/inception.mp3";
            break;
        case 6:
            cap.open("resources/speed.mp4");
            mp3Filepath = "resources/speed.mp3";
            break; 
        default:
            break;
        }
        wclear(playerWindow);
        wrefresh(playerWindow);
        double fps = cap.get(cv::CAP_PROP_FPS);
        wmove(playerWindow, 0, 0);
        bool once = false;
        int playerWindowHeight, playerWindowWidth;
        getmaxyx(playerWindow, playerWindowHeight, playerWindowWidth);
        Audio audio(mp3Filepath);
        audio.play();
        for(;;) {
            auto start = std::chrono::high_resolution_clock::now();
            cap >> frame;
            if(frame.empty()) {
                clear_window(playerWindow);
                break;
            }
            cv::resize(frame, frame, cv::Size(playerWindowWidth, playerWindowHeight));
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            cv::Size sz = frame.size();
            videoWidth = sz.width;
            videoHeight = sz.height;
            for(int i = 0; i < videoHeight; ++i) {
                for(int j = 0; j < videoWidth; ++j) {
                    uchar intensity = frame.at<uchar>(i, j);
                    char asciiPixel = pixelToASCII(intensity);
                    mvaddch(i, j, asciiPixel);
                }
            }
            if(!once) {
                wclear(menuWindow);
                draw_menu(menuWindow, menuItem);
                once = true;
            }
            refresh();
            auto end = std::chrono::high_resolution_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            napms(1000 / fps - time_span.count());

            nodelay(menuWindow, true);
            option = wgetch(menuWindow);
            nodelay(menuWindow, false);
 
            if(option == 'q' || option == 'Q') {
                quit = true;
                option = '\0';
                cap.release();
                break;
            } else if(option == 'm' || option == 'M') {
                clear_window(playerWindow);
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
