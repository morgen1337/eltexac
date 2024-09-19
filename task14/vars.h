#define MSGSIZE 256
#define MAXQ 20
#define USERNAMESIZE 32
#define SHMNAME "/shm"
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
struct Chat *chat;