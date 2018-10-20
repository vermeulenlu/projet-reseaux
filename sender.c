char file[100];

int main(argc, *argv[])
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
        file=optarg;
        break;
        default:
        fprintf(stderr, "Arguments supplémentaire non-reconnus\n");
        return 1;
      }
    }
  }

}
