#define MSGSIZE 256
#define MAXQ 10
#define USERNAMESIZE 32
struct usermessages{
    char username[USERNAMESIZE];
    char msg[MSGSIZE];
};
struct Chat{
    struct usermessages messages[MAXQ];
    char usernames[MAXQ][USERNAMESIZE];
    int clientcount;
    int nmessages;
};
struct Chat chat;
int messagecount = 0; 
char usernames[MAXQ][USERNAMESIZE];
int n = sizeof(struct usermessages);


mqd_t receive;
mqd_t send;