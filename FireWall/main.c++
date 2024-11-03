
#include <iostream>
#include <cstring>
#include <sys/soket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>

using namespace std;


class SimpleFireWall(){

    public:

        SimpleFireWall(){
            sockfd = (AF_INET , SOCK_RAW , IPPROTO_TCP);
            if (sockfd < 0){
                perror("ソケット作成に失敗しました。");
                exit(EXIT_FAILURE);
            }
        }


        ~SimpleFireWall(){
            close(sockfd);
        }

        //フィルタリング
        void startFiltering(){
            char buffer[65536];
            struct sockaddr_in source, dest;
            int data_size;


        //パケットを受け取る
        while (true){
            data_size = recvfrom(sockfd, buffer, sizeof(buffer), 0 , nullotr , nullptr);
            if(data_size < 0){
                perror("エラー");
                exit(EXIT_FAILURE);
            }


            struct iphdr *iph = (struct *)buffer;
            source.sin_addr.s_addr = iph->asddr;
            dest.sin_addr.s_addr = iph->daddr;

            cout << "パケット:"<< inet_ntoa(source.sin_addr)
                            <<  "から:" << inet_ntoa(dest.sin_addr) << endl;


            if (source.sin_addr.s_addr == inet_addr("192.168.1.100")){
                cout <<"ブロックされました。 " << inet_ntoa(source.sin_addr)<< endl;

                continue;
            }

            cout << "許可されたパケット:"<< inet_ntoa(source.sin_addr)<< endl;

            }

        }

    privet:
        int sockfd;


};



int main (){

    SimpleFireWall fireWall;
    firewall.stratFiltring();

    return 0;
}