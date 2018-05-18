###
# FORMATTING
#   The ANSI/VT100 terminals and terminal emulators are not just able to display black and white text ;
#   they can display colors and formatted texts thanks to escape sequences.
#   This include use UTF-8 format!
###
#export LANG=C.UTF-8

# Escape secuence
ESC_S="$(printf '\033')"

# SET: Force to set an attribute
FC_BOLD="${ESC_S}[1m"         # Bold/Bright
FC_DIM="${ESC_S}[2m"          # Dim
FC_UNDERLINED="${ESC_S}[4m"   # Underlined
FC_BLINK="${ESC_S}[5m"        # Blink
FC_REVERSE="${ESC_S}[7m"      # Reverse (invert the foreground and background colors)
FC_HIDDEN="${ESC_S}[8m"       # Hidden (useful for passwords)

# RESET: Force to remove an attribute
FC_RESET="${ESC_S}[0m"       # Reset all attributes

# 8/16 FOREGROUND COLOR
FC_FG_DEFAULT="${ESC_S}[39;1m"          # DEFAULT foreground font
FC_FG_BLACK="${ESC_S}[30;1m"            # BLACK foreground font
FC_FG_RED="${ESC_S}[31;1m"              # RED foreground font
FC_FG_GREEN="${ESC_S}[32;1m"            # GREEN foreground font
FC_FG_YELLOW="${ESC_S}[33;1m"           # YELLOW foreground font
FC_FG_BLUE="${ESC_S}[34;1m"             # BLUE foreground font
FC_FG_MAGENTA="${ESC_S}[35;1m"          # MAGENTA foreground font
FC_FG_CYAN="${ESC_S}[36;1m"             # CYAN foreground font
FC_FG_LIGHTGRAY="${ESC_S}[37;1m"        # LIGHTGRAY foreground font
FC_FG_DARKGRAY="${ESC_S}[90;1m"         # DARKGRAY foreground font
FC_FG_LIGHTRED="${ESC_S}[91;1m"         # LIGHTRED foreground font
FC_FG_LIGHTGREEN="${ESC_S}[92;1m"       # LIGHTGREEN foreground font
FC_FG_LIGHTYELLOW="${ESC_S}[93;1m"      # LIGHTYELLOW foreground font
FC_FG_LIGHTBLUE="${ESC_S}[94;1m"        # LIGHTBLUE foreground font
FC_FG_LIGHTMAGENTA="${ESC_S}[95;1m"     # LIGHTMAGENTA foreground font
FC_FG_LIGHTCYAN="${ESC_S}[96;1m"        # LIGHTCYAN foreground font
FC_FG_WHITE="${ESC_S}[97;1m"            # WHITE foreground font

# 8/16 BACKGROUND COLOR
FC_BG_DEFAULT="${ESC_S}[49;1m"          # DEFAULT background font
FC_BG_BLACK="${ESC_S}[40;1m"            # BLACK background font
FC_BG_RED="${ESC_S}[41;1m"              # RED background font
FC_BG_GREEN="${ESC_S}[42;1m"            # GREEN background font
FC_BG_YELLOW="${ESC_S}[43;1m"           # YELLOW background font
FC_BG_BLUE="${ESC_S}[44;1m"             # BLUE background font
FC_BG_MAGENTA="${ESC_S}[45;1m"          # MAGENTA background font
FC_BG_CYAN="${ESC_S}[46;1m"             # CYAN background font
FC_BG_LIGHTGRAY="${ESC_S}[47;1m"        # LIGHTGRAY background font
FC_BG_DARKGRAY="${ESC_S}[100;1m"         # DARKGRAY background font
FC_BG_LIGHTRED="${ESC_S}[101;1m"         # LIGHTRED background font
FC_BG_LIGHTGREEN="${ESC_S}[102;1m"       # LIGHTGREEN background font
FC_BG_LIGHTYELLOW="${ESC_S}[103;1m"      # LIGHTYELLOW background font
FC_BG_LIGHTBLUE="${ESC_S}[104;1m"        # LIGHTBLUE background font
FC_BG_LIGHTMAGENTA="${ESC_S}[105;1m"     # LIGHTMAGENTA background font
FC_BG_LIGHTCYAN="${ESC_S}[106;1m"        # LIGHTCYAN background font
FC_BG_WHITE="${ESC_S}[107;1m"            # WHITE background font

# UTF-8 ICONS
ICON_POINTS="…"
ICON_TICK="✔"
ICON_LIGHTINING="⚡"
ICON_CROSS="✘"
ICON_SUN="☀"
ICON_STAR1="★"
ICON_STAR2="☆"
ICON_BOXEMPTY="☐"
ICON_BOXTICKED="☑"
ICON_BOXCROSSED="☒"
ICON_DIE="☠"
ICON_RADIACTIVE="☢"
ICON_SOVIET="☭"
ICON_PEACE="☮"
ICON_SMILE="☻"
ICON_SUN2="☼"
ICON_MOON="☾"
ICON_GIRL="♀"
ICON_BOY="♂"
ICON_CHESSKING="♔"
ICON_CHESSQUEEN="♕"
ICON_CHESSTOWER="♖"
ICON_CHESSBISHOP="♗"
ICON_CHESSHORSE="♘"
ICON_CHESSPAWN="♙"
ICON_CHESSKING2="♚"
ICON_CHESSQUEEN2="♛"
ICON_CHESSTOWER2="♜"
ICON_CHESSBISHOP2="♝"
ICON_CHESSHORSE2="♞"
ICON_CHESSPAWN2="♟"
ICON_SPADE="♠"
ICON_HEART="♡"
ICON_DIAMOND="♢"
ICON_CLUB="♣"
ICON_SPADE2="♤"
ICON_HEART2="♥"
ICON_DIAMOND2="♦"
ICON_CROTCHET="♩"
ICON_QUAVER="♪"
ICON_DQUAVER="♫"
ICON_FLAT="♭"
ICON_NATURAL="♮"
ICON_SHARP="♯"
ICON_RECYCLE="♻"
ICON_WHEELCHAIR="♿"
ICON_DICE1="⚀"
ICON_DICE2="⚁"
ICON_DICE3="⚂"
ICON_DICE4="⚃"
ICON_DICE5="⚄"
ICON_DICE6="⚅"
ICON_BFLAG="⚐"
ICON_WFLAG="⚑"
ICON_WORKING="⚒"
ICON_ANCHOR="⚓"
ICON_BATTLE="⚔"
ICON_JUSTICE="⚖"
ICON_CAUTION="⚠"
ICON_KEY="⚷"
ICON_PICKAXE="⛏"
ICON_BRIGHT="⛭"

function LOGD()
{
    local begin_msg=$1
    echo -e "${FC_FG_LIGHTBLUE}[${ICON_POINTS}] ${begin_msg}...${FC_RESET}"
}

function LOGV()
{
    local info_msg=$1
    echo -e "${FC_FG_DARKGRAY}${info_msg}${FC_RESET}"
}

function LOGI()
{
    local info_msg=$1
    echo -e "${FC_FG_LIGHTGRAY}${info_msg}${FC_RESET}"
}

function LOGOK()
{
    local ok_msg=$1
    echo -e "${FC_FG_GREEN}[${ICON_TICK}] ${ok_msg}${FC_RESET}"
}

function LOGW()
{
    local warning_msg=$1
    echo -e "${FC_FG_YELLOW}[${ICON_LIGHTINING}] Warning: ${warning_msg}${FC_RESET}"
}

function LOGE()
{
    local error_msg=$1
    echo -e "${FC_FG_RED}[${ICON_CROSS}] Error: ${error_msg}${FC_RESET}"
}

