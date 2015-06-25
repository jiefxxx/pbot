#include <tools/socket.h>
#include <tools/utils.h>

#define BUFLEN 512 

struct Psocket* init_Psocket(int type,int server,int port,char* addr){

	struct Psocket* ps = (struct Psocket*)malloc(sizeof(struct Psocket));
	struct sockaddr_in* si = NULL;
	struct sockaddr_un* su = NULL;
	ps->type = type;
	ps->server = server;
	
	ps->socket = -1;
	if(ps->type==1){
	
		ps->socket = socket(PF_LOCAL,SOCK_STREAM,0);
		
		ps->sockaddr = malloc(sizeof(struct sockaddr_un));
		su = (struct sockaddr_un*)ps->sockaddr;
		
		su->sun_family = AF_LOCAL;
		strcpy(su->sun_path, addr);
		
	}
	else if(ps->type==2||ps->type==3){
	
		ps->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
		ps->sockaddr = malloc(sizeof(struct sockaddr_in));
		si = (struct sockaddr_in*)ps->sockaddr;
		
		si->sin_family = AF_INET;
		si->sin_port = htons(port);
		si->sin_addr.s_addr = htonl(INADDR_ANY);
		
	}
	else{
		ps->socket = -1;
		ps->sockaddr = NULL;
	}
	
	if(ps->socket == -1) {
		if(ps->sockaddr != NULL){
			free(ps->sockaddr);
		}
		free(ps);
		return NULL;
	}
	
	if(server){
		switch(ps->type){
			case 1:
			
				if(bind(ps->socket,(struct sockaddr*)ps->sockaddr,SUN_LEN((struct sockaddr_un*)ps->sockaddr))==-1){
					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
				listen(ps->socket,5);
				
				break;
			
			case 2:
				
				if(bind(ps->socket,(struct sockaddr*)ps->sockaddr,sizeof(struct sockaddr_in))==-1){
					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
				
				break;
			
			case 3:
				if(bind(ps->socket,(struct sockaddr*)ps->sockaddr,sizeof(struct sockaddr_in))==-1){
					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
			
				struct ip_mreq mreq;
				mreq.imr_multiaddr.s_addr = inet_addr(addr);         
				mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
				if (setsockopt(ps->socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
 					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
				
			default:
			
				free(ps->sockaddr);
				free(ps);
				return NULL;
		
		}
	}
	
	else{
		switch(ps->type){
			case 1:
				if(connect(ps->socket,(struct sockaddr*)ps->sockaddr,SUN_LEN((struct sockaddr_un*)ps->sockaddr))==-1){
					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
				
				break;
			
			case 2:
				if(si==NULL){
					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
				si->sin_addr.s_addr = inet_addr(addr);
				
				break;
			
			case 3:
				if(si==NULL){
					free(ps->sockaddr);
					free(ps);
					return NULL;
				}
				si->sin_addr.s_addr = inet_addr(addr);
				
				break;
			
			default:
				free(ps->sockaddr);
				free(ps);
				return NULL;
		
		}
	}
	return ps;
}
//work on it.... 
int send_Psocket(struct Psocket* ps,struct Pmessage message,void* data){
	if(ps->server){
		return -2;
	}
	void* mes = malloc(sizeof(struct Pmessage)+message.len);
	memcpy(mes,&message,sizeof(struct Pmessage));
	memcpy(mes+sizeof(struct Pmessage),data,message.len);
	int len = sizeof(struct Pmessage)+message.len;
	int ret;
	switch(ps->type){
		case 1:
			ret = write(ps->socket,mes,len);
			
			break;
		case 2:
			ret = sendto(ps->socket,mes,len,0,(struct sockaddr*)ps->sockaddr,sizeof(struct sockaddr));
			
			break;
		case 3:
			ret = sendto(ps->socket,mes,len,0,(struct sockaddr*)ps->sockaddr,sizeof(struct sockaddr));
			
			break;
		default:
			ret =  -1;
			
			break;
	}
	free(mes);
	return ret;
}

/*struct Pmessage* receve_Psocket(struct Psocket* ps){
	switch(ps->type){
		case 1:
			
		case 2:
			
		case 3:
			
		default:
			return NULL;
	}
}*/


