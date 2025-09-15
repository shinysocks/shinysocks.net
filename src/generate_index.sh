#!/bin/bash

lav='\e[1;35m'
italav='\e[3;35m'
blue='\e[3;34m'
reset='\e[1;0m'
green='\e[1;32m'
yellow='\e[1;33m'


# logo
printf "\n"
printf "$lav"
printf "  ▄▄▄▗▖▗▖▄▗▖ ▄▗▖▗▖▄▄▄▗▄▄▖▄▄▗▖▗▖▄▄▄\n"
printf "  █▄▄▐▙▟▌█▐█▖█▝▙▟▘█▄▄▐▌▐▌█ ▐▙█▘█▄▄\n"
printf "  ▄▄█▐▌▐▌█▐▌▜█ ▐▌ ▄▄█▐▙▟▌█▄▐▌▜▌▄▄█\n"
printf "\n\n"

# hyperlinks
printf "$lav"
printf "  hyperlinks\n\n"
printf "$blue"
printf "    https://github.com/shinysocks\n"
printf "    https://shinysocks.net/resume.pdf\n"
printf "    https://linkedin.com/in/noah-dinan\n"
printf "    https://steamcommunity.com/profiles/76561199074928968\n"
printf "    mailto:noah@shinysocks.net\n\n"

# about me
printf "$reset"
printf "$lav"
printf "  about me\n\n"
printf "$reset"

printf "    Hey, my name is Noah Dinan and I am currently studying\n"
printf "    Software Engineering at Milwaukee School of Engineering\n"
printf "    and working part time at Northwestern Mutual.\n\n"

printf "    I'm a cat lover, computer programmer, vocalist, cyclist and videogamer\n"
printf "    currently daily-driving debian on WSL2 and writing code in neovim\n"
printf "    avid hater of generative ai and technofacism\n\n"

# endpoints
printf "$reset$lav"
printf "  endpoints\n\n"
printf "$green"
printf "     GET /pong\n"
printf "     GET /shared_file\n"
printf "     GET /radio | sh\n\n"

# portfolio
printf "$reset$lav"
printf "  recent work\n\n"


printf "$yellow"
printf "     Re-Re-Rewrite shinysocks.net\n"
printf "$blue"
printf "     https://github.com/shinysocks/shinysocks.net\n"
printf "$reset"
printf "     Rewrote shinysocks.net for the third? time in c++\n\n"

printf "$yellow"
printf "     Arts at Large Gamedev Workshop\n"
printf "$blue"
printf "     https://github.com/shinysocks/artsatlarge_gamedev\n"
printf "$reset"
printf "     Developing a simple gamedev workshop using pygame and piskel\n\n"


printf "$yellow"
printf "     Phone Booth\n"
printf "$blue"
printf "     https://github.com/shinysocks/phonebooth\n"
printf "$reset"
printf "     wrote source code for an interactive art installation\n"
printf "     by Daisy DiCarlo entitled Phone Booth\n\n"


# footer
printf "$reset$italav"
printf "  shinysocks.net is hosted on aws (for now)\n\n"
printf "$reset"
