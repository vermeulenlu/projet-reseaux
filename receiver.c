


/////////////////////////////////////////////////////////////
////////////////////DECLARATIONS/////////////////////////////
/////////////////////////////////////////////////////////////

char filename[100];
struct_sockadrr_in6 *rval;
int isFile=0;
File *file =NULL;
int y =0;

/////////////////////////////////////////////////////////////
////////////////////////////MAIN/////////////////////////////
/////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{
  if(argc<3)
  {
    fprintf(stderr,"Missing arguments\n");
    return 1;
  }
  if(argc>3)
  {
    int opt;
    while((opt=getopt(argc,argv,"f:"))!=-1)
    {
      switch(opt)
      {
        case 'f':
        filename=optarg;
        isFile=1;
        break;
        default:
        fprintf(stderr, "Argument(s) supplémentaire(s) non-reconnus\n");
        return 1;
      }
    }
  }

  int port = atoi(argv[argc-1]);
  char *address = real_address(argv[argc-2],&rval);

  int sfd = create_socket(&rval,port,NULL,-1);
  if(sfd<0)
  {
    fprintf(stderr, "Erreur lors de la création du socket\n");
    return 2;
  }

  if(isFile=1)
  {
    file=fopen(filename,O_WRONLY);
    if(file==NULL)
    {
      fprintf(stderr, "Impossible d'ouvrir le fichier\n", );
      return 3;
    }
          while(1)
          {
            pkt_t *sendback;// packet de réponse
            sendback = pkt_new();
            pkt_t *reception;// packet de réception
            reception = pkt_new();
            char *buffer;// buffer pour prendre les information placées sur le socket
            memset(buffer,0,MAX_PKT_SIZE);

            struct pollfd ufds;
            ufds.fd=sfd;
            ufds.events=POLLIN;
            int rv;
            rv=poll(ufds,1,-1);// On attend une connexion
            if(rv<0)
            {
              fprintf(stderr, "Erreur dans le poll\n");
              return 4;
            }
            if(ufds.revents & POLLIN)
            {
              int y = recvfrom(sfd,buffer,MAX_PKT_SIZE,0,(struct sockadrr *)rval ,sizeof(struct sockaddr_in6));
              if(y<0)
              {
                break;
              }
              pkt_status_code status = decode(buffer,y,reception);// On decode l'information du buffer et on met dans une struct pkt
              if(status!=PKT_OK)
              {
                fprintf(stderr, "Erreur de le décodage du socket\n");
                return 5;
              }
              ptypes_t type = pkt_get_type(reception);
              if(type==PTYPE_DATA)
              {

              }
              if(type==PTYPE_ACK)
              {

              }
              if(type==PTYPE_NACK)
              {

              }
            }
          }
    }
  }
}
