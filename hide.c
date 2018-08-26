/* Hide Manager by Levak 26/03/12 */

#include <os.h>
#include <libndls.h>
#define MAXLEN 10
#define QUOTE_X(t)#t
#define QUOTE(t)QUOTE_X(t)

static char *title = "Hide manager says";
static char *errorRMsg = "Error while revealing the hidden data.\nData may be lost !";
static char *errorHMsg = "Error while hiding directory.\nPlease create a directory named \"hidden\" at the root of your documents.";
static char *errorUninst = "Hide Manager is not installed yet.";
static char *successUninst = "Hide Manager successfully deleted the config file !";
static char *welcome1Msg = "Hi, welcome to Hide Manager !\nThis program lets you hide a complete directory from TI-Nspire default file listing !\nPRESS ENTER TO CONTINUE\nLevak";
static char *welcome2Msg = " Fine, We are going to create a directory named \"hidden\" at the root of yours documents. This directory is hidden when \nyou want to and shown otherwise.\n The name of the hidden directory cannot be changed, but you can put everything you \nwant in it and all its content will be hidden !\nPRESS ENTER TO CONTINUE";
static char *welcome2bMsg = "Oh ! Hide Manager detected that a \ndirectory named \"hidden\" already exists !\nThis directory is hidden when you want to \nand shown otherwise.\n The name of the hidden directory cannot be changed, but you can put everything \nyou want in it and all its content will be \nhidden !\nPRESS ENTER TO CONTINUE";
static char *welcome3Msg = "Now we are going to secure this a little bit.\nLet's enter a password of maximum " QUOTE(MAXLEN) " characters.\nPRESS ENTER TO CONTINUE";
static char *welcome4Msg = "Congratulations !\nHide Manager is now set up, test it !\n\nVisit http://tiplanet.org/ for more TI-Nspire programs !";
static char *welcome4bMsg = "Setup canceled";
static char *confirmUninst = "Do you really want to uninstall Hide Manager ?";
//static char *enterPasswd = "Enter your password";
static char *yes = "Yes";
static char *no = "No";
static char *origin = "/documents/hidden/";
static char *hidden = "/hidden/";

void rename_prgm (BOOL hide, char *path) {
    int len = strlen(path);
    char self_origin[len + 10];
    char self_hidden[len + 10];

    strcpy(self_origin, path);
    strcpy(self_hidden, path);
    strcat(self_origin, "hide.tns");
    strcat(self_hidden, "reveal.tns");

    if (hide)
        rename(self_origin, self_hidden);
    else
        rename(self_hidden, self_origin);
}

int hide (BOOL hide, char *path)
{
    int error;

    if (hide)
        error = rename(origin, hidden);
    else
        error = rename(hidden, origin);

    if (!error)
        rename_prgm(hide, path);

    return error;
}

/* From particles by ExtendeD */
inline void setPixel(int x, int y, int r, int g, int b) {
    if(lcd_isincolor()) {
        unsigned short* p = (unsigned short*)(SCREEN_BASE_ADDRESS + (x << 1) + (y << 9) + (y << 7));
        *p = (r >> 3) | ((g >> 2) << 5) | ((b >> 3) << 11);
    }
    else {
        unsigned char* p = (unsigned char*)(SCREEN_BASE_ADDRESS  + ((x >> 1) + (y << 7) + (y << 5)));
        *p = (x & 1) ? ((*p & 0xF0) | r) : ((*p & 0x0F) | (r << 4));
    }
}
/* End of particles */

void fillCircle(int x, int y, int r) {
    int i, j;
    for(i = -r; i < r; ++i)
        for(j = -r; j < r; ++j) {
            int v = i*i + j*j - r*r;
            if(v < 0 && v > -40 )
                setPixel(x+i, y+j, 0, 0, 0);
            else if(v < 0)
                setPixel(x+i, y+j, 255, 255, 255);
        }
}

void fillRect(int x1, int y1, int x2, int y2) {
    int i, j;
    for(i = x1; i < x2; ++i)
        for(j = y1; j < y2; ++j)
            setPixel(i, j, 0, 0, 0);
}

void drawRect(int x1, int y1, int x2, int y2) {
    int i, j;
    int margin = 2;
    for(i = x1; i < x2; ++i)
        for(j = y1; j < y2; ++j)
            if(i < x1 + margin || i > x2 - margin 
               || j < y1 + margin || j > y2 - margin)
                setPixel(i, j, 255, 255, 255);
}

char request_char(void) {
    char key = 0;
    wait_no_key_pressed();
    while (key == 0) {
        wait_key_pressed();
        if(isKeyPressed(KEY_NSPIRE_0)) key = '0';
        if(isKeyPressed(KEY_NSPIRE_1)) key = '1';
        if(isKeyPressed(KEY_NSPIRE_2)) key = '2';
        if(isKeyPressed(KEY_NSPIRE_3)) key = '3';
        if(isKeyPressed(KEY_NSPIRE_4)) key = '4';
        if(isKeyPressed(KEY_NSPIRE_5)) key = '5';
        if(isKeyPressed(KEY_NSPIRE_6)) key = '6';
        if(isKeyPressed(KEY_NSPIRE_7)) key = '7';
        if(isKeyPressed(KEY_NSPIRE_8)) key = '8';
        if(isKeyPressed(KEY_NSPIRE_9)) key = '9';
        if(isKeyPressed(KEY_NSPIRE_A)) key = 'A';
        if(isKeyPressed(KEY_NSPIRE_B)) key = 'B';
        if(isKeyPressed(KEY_NSPIRE_C)) key = 'C';
        if(isKeyPressed(KEY_NSPIRE_D)) key = 'D';
        if(isKeyPressed(KEY_NSPIRE_E)) key = 'E';
        if(isKeyPressed(KEY_NSPIRE_F)) key = 'F';
        if(isKeyPressed(KEY_NSPIRE_G)) key = 'G';
        if(isKeyPressed(KEY_NSPIRE_H)) key = 'H';
        if(isKeyPressed(KEY_NSPIRE_I)) key = 'I';
        if(isKeyPressed(KEY_NSPIRE_J)) key = 'J';
        if(isKeyPressed(KEY_NSPIRE_K)) key = 'K';
        if(isKeyPressed(KEY_NSPIRE_L)) key = 'L';
        if(isKeyPressed(KEY_NSPIRE_M)) key = 'M';
        if(isKeyPressed(KEY_NSPIRE_N)) key = 'N';
        if(isKeyPressed(KEY_NSPIRE_O)) key = 'O';
        if(isKeyPressed(KEY_NSPIRE_P)) key = 'P';
        if(isKeyPressed(KEY_NSPIRE_Q)) key = 'Q';
        if(isKeyPressed(KEY_NSPIRE_R)) key = 'R';
        if(isKeyPressed(KEY_NSPIRE_S)) key = 'S';
        if(isKeyPressed(KEY_NSPIRE_T)) key = 'T';
        if(isKeyPressed(KEY_NSPIRE_U)) key = 'U';
        if(isKeyPressed(KEY_NSPIRE_V)) key = 'V';
        if(isKeyPressed(KEY_NSPIRE_W)) key = 'W';
        if(isKeyPressed(KEY_NSPIRE_X)) key = 'X';
        if(isKeyPressed(KEY_NSPIRE_Y)) key = 'Y';
        if(isKeyPressed(KEY_NSPIRE_Z)) key = 'Z';

        if(isKeyPressed(KEY_NSPIRE_UP)) key = 1;
        if(isKeyPressed(KEY_NSPIRE_DOWN)) key = 1;
        if(isKeyPressed(KEY_NSPIRE_LEFT)) key = 1;
        if(isKeyPressed(KEY_NSPIRE_RIGHT)) key = 1;

        if(isKeyPressed(KEY_NSPIRE_ESC)) key = 1;
        if(isKeyPressed(KEY_NSPIRE_DEL)) key = 2;
        if(isKeyPressed(KEY_NSPIRE_ENTER)) key = 3;
        wait_no_key_pressed();
    }
    return key;
}

int request_pwd(char * password, int maxlen) {

    int len = 0;
    char key = 0;
    int i;
    int r = 10;
    int offset = 10;
    int size = (2*r + offset)/2;

    /* Extra screen buffer */
    char *sbuffer = sbuffer = malloc(SCREEN_BYTES_SIZE);
    memcpy(sbuffer, SCREEN_BASE_ADDRESS, SCREEN_BYTES_SIZE);

    /* Main Loop */
    while (len < maxlen && key != 3){
        key = request_char();
        if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'Z'))
            password[len++] = key;
        else if (key == 2 && len > 0) /* Backspace */
            len--;
        else if (key == 1)  /* Esc key */
            return 1;

        memcpy(SCREEN_BASE_ADDRESS, sbuffer, SCREEN_BYTES_SIZE);
        for(i = 0; i < len; ++i)
            fillCircle(140 - (2*i - len)*size + offset/2, 220, r);
    }
    password[len] = 0;
    free(sbuffer);
    return 0;
}

int main(int argc, char* argv[]) {

    if(argc < 1) return 0;

    char *config_path = "/documents/config.hide";

    int len = strlen(argv[0]);
    char path[len];
    strcpy(path, argv[0]);
    char *p = strrchr(path, '/');
    char self_name[len - ((p) ? p - path + 1: 0) + 1];
    strcpy(self_name, (p) ? p + 1: path);

    if(strcmp(self_name, "uninstall.tns") == 0) {
        if (show_msgbox_2b(title, confirmUninst, yes, no) == 2)
            return 0;
        if(remove(config_path) == 0)
            show_msgbox(title, successUninst);
        else
            show_msgbox(title, errorUninst);
        return 0;
    }

    if(p) *(p + 1) = 0;

    if (is_cx) lcd_incolor();

    FILE *config; /* Contains password */
    config = fopen (config_path, "r");
    if (config != NULL) {
        if(chdir (hidden) == 0) { /* if there is something to reveal */
            fseek(config, 0, SEEK_END);
            unsigned length = ftell(config);
            rewind(config);
            char realpass[length+1];
            char password[length+1];
            fread(realpass, sizeof(char), length, config);
            realpass[length] = 0;
            fclose(config);
            if(length != 0) { /* No password needed */
                if(request_pwd(password, length) == 0) {
//                    printf("%s, %d, %s\n", realpass, length, password);
                    if (strcmp(password, realpass)) /* If password doesn't match */
                        return 0;
                }
                else
                    return 0;
            }
        }
        else fclose(config); /* No need of config if we want to hide */
    }
    else {
        /* Welcome, First use */
        show_msgbox(title, welcome1Msg);

        /* Create hidden directory */

        if (mkdir(hidden, 0) == -1) { /* Hidden directory already exists */
            show_msgbox(title, welcome2bMsg);
            rename_prgm(TRUE, path);
        }
        else if (mkdir(origin, 0) == 0) { /* Visible directory doesn't exist */
            rmdir(hidden); /* We created a useless folder, so deleted it */
            show_msgbox(title, welcome2Msg);
        }
        else /* Visible directory already exists */
            show_msgbox(title, welcome2bMsg);

        refresh_osscr();
        show_msgbox(title, welcome3Msg);

        /* Saving password */

        fillRect(0, 200, 320, 240);
        drawRect(5, 205, 315, 235);

        char password[MAXLEN + 1];
        if(request_pwd(password, MAXLEN) == 0)
        {
            config = fopen(config_path, "w");
            fputs(password, config);
            fclose(config);
            show_msgbox(title, welcome4Msg);
        }
        else
            show_msgbox(title, welcome4bMsg);
        return 0;
    }

    BOOL h = FALSE;
    int error = hide(h, path);
    if (error) {
        h = TRUE;
        error = hide(h, path);
    }

    if (error){
        puts("Error hidding directory");
        show_msgbox(title, (h)?errorHMsg:errorRMsg);
    }

    wait_no_key_pressed();

    refresh_osscr();

    return 0;
}
