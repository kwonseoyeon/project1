/* 운영체제 스케줄링 알고리즘 프로그래밍(2014/11/29)
 * 201158062 송승현
 * c언어를 활용한 단일 프로세서의 프로세스 스케줄링 알고리즘을 4단계에 걸쳐 구현한 프로그램
 */

#include<stdio.h> 
#include<conio.h> 
#include<string.h> 

int n,Bu[20],Twt,Ttt,A[20],Wt[20],w;
float Awt,Att;
char pname[20][20],c[20][20];

struct p_inform{ //프로세스의 이름, 도착시간,실행시간,대기시간을 구조체로 엮어놓음.
	char p_name[20];	//프로세스이름
	int ctime;			//도착시간
	int btime;			//실행시간
	int wtime;			//대기시간
} p[20];

void Getdata(); 
void Gantt_chart(); 
void Calculate(); 
void sortProcess();
void FCFS(); 
void SRTF();
void SJF();
void R_R();

//GETTING THE NUMBER OF PROCESSES AND THE BURST TIME AND ARRIVAL TIME FOR EACH PROCESS 
void main() 
{ 
    int ch; 
	while(1){
		printf("==================================================================\n");
		printf("\n  		****** 알고리즘 선택 ******\n\n");
		printf("1)FCFS		2)SJF		3)SRTF		4)R_R \n\n");
		printf("==================================================================\n");
		printf("\n\n<< 원하시는 스케줄링 알고리즘을 선택하세요 >>\n");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				Getdata();
				FCFS();
				break;
			case 2:
				Getdata();
				SJF();
				break;
			case 3:
				Getdata();
				SRTF();
				break;
			case 4:
				Getdata();
				R_R();
				break;
			default:
				printf("없는 번호를 선택하셨습니다.\n");
				break;
		}
		printf("\n\n\n");
	}

}

void Getdata() 
{ 
	printf("\n*** 몇개의 프로세스를 만들겠습니까 : "); 
	scanf("%d",&n); 

	 for(int i=1;i<=n;i++) { 
		fflush(stdin); 
		printf("\n\n * 프로세스이름을 입력하세요 : ");  
		scanf("%s",&p[i].p_name);
		
		printf("*  %s의 도착시간을 입력하세요 =  ",p[i].p_name); 
		scanf("%d",&p[i].ctime); 
		
		printf("*  %s의 실행시간을 입력하세요  = ",p[i].p_name); 
		scanf("%d",&p[i].btime);
	} 
} 

//DISPLAYING THE GANTT CHART 
void Gantt_chart() 
{ 

	printf("\n\n\t\t\t< GANTT CHART >\n"); 
	printf("\n-----------------------------------------------------------\n"); 

	for(int i=1;i<=n;i++) 
		printf("|\t%s\t",p[i].p_name); 
	
    printf("|\t\n"); 
	printf("\n-----------------------------------------------------------\n"); 
	printf("\n"); 

	for(int i=1;i<=n;i++) 
		printf("%d\t\t",p[i].wtime); 
	printf("%d",p[n].wtime+p[n].btime); 
	printf("\n-----------------------------------------------------------\n"); 
	printf("\n"); 
} 


//CALCULATING AVERAGE WAITING TIME AND AVERAGE TURN AROUND TIME 
void Calculate() 
{
	Wt[1]=0; //For the 1st process 
	for(int i=1;i<=n;i++) { 
		p[i].wtime=p[i-1].btime+p[i-1].wtime;
		//Wt[i]=Bu[i-1]+Wt[i-1]; 
	} 
    for(int i=1;i<=n;i++) { 
		Twt=Twt+(p[i].wtime-p[i].ctime);//(Wt[i]-A[i]) 
		Ttt=Ttt+((p[i].wtime+p[i].btime)-p[i].ctime);//((Wt[i]+Bu[i])-A[i]); 
    } 
    Att=(float)Ttt/n; 
    Awt=(float)Twt/n; 

	printf("\n\n Average Turn around time=%3.2f ",Att);  
    printf("\n\n AverageWaiting Time=%3.2f ",Awt); 
} 

//FCFS Algorithm 
void FCFS() 
{ 
    int i,j,temp, temp1; 
    Twt=0; 
    Ttt=0; 
    printf("\n\n << FIRST COME FIRST SERVED ALGORITHM >>\n\n"); 
	
    for(i=1;i<=n;i++) { 
        for(j=i+1;j<=n;j++) { 
			if(p[i].ctime>p[j].ctime) { //n번의도착시간이 n+1번보다 크면(늦으면) 
				temp=p[i].btime;; 
				temp1=p[i].ctime;
				p[i].btime=p[j].btime; 
				p[i].ctime=p[j].ctime; 
				p[j].btime=temp;
				p[j].ctime=temp1; 
				strcpy(c[i],p[i].p_name); 
				strcpy(p[i].p_name,p[j].p_name);
				strcpy(p[j].p_name,c[i]);
            } 
        } 
    } 

   Calculate(); 
   Gantt_chart(); 

} 

//SJF Algorithm
void SJF()
{
	int temp, temp1,num=0, n1=1;
    Twt=0; 
    Ttt=0; 
    printf("\n\n << SHORTEST JOB FIRST ALGORITHM >>\n\n"); 
	
	sortProcess();

	num=p[n1].btime;
	for(int i=n; i>1;i--){
		for(int j=2; j<i; j++){
			if(num>p[j].ctime){ //num이 p[j]의 도착시간보다 더 크면
				if(p[j].btime>p[j+1].btime){ // p[j]의 실행시간이 p[j+1]의 실행시간보다 크면 교체
				temp=p[j].btime;
				temp1=p[j].ctime;
				p[j].btime=p[j+1].btime;
				p[j].ctime=p[j+1].ctime;
				p[j+1].btime=temp;
				p[j+1].ctime=temp1;
				strcpy(c[j],p[j].p_name);
				strcpy(p[j].p_name,p[j+1].p_name);
				strcpy(p[j+1].p_name,c[j]);
				}
			}
		 }
		n1+=1;
		num+=p[n1].btime; // 0번째 이후에서 i+1번째 프로세스도착시간이 i의 실행시간보다 적으면 더하기.
	}
   Calculate(); 
   Gantt_chart();
}

//SRTF Algorithm
void SRTF(){
	int n1=1, k=1,num=0, count=0, temp, temp1;
	int nextArrival=0;//도착시간이 현재진행시간보다 작은 프로세스들중에 하나만 들어오게하기 위해 만든 변수
	p_inform real_p[15];
	Twt=0; 
    Ttt=0; 
    
	printf("\n\n << SHORTEST REMAINING TIME FIRST ALGORITHM >>\n\n"); 
	
	sortProcess();
	
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			if(num>=p[j-1].ctime){ //현재 실행시간보다 도착시간이 작을 경우
				count++; //도착시간이 작은 프로세스들을 정렬하기 위한 카운트.
				if(p[j].ctime-p[i].ctime>0){ //p[j]의 도착시간 - p[i]의 도착시간이 0보다 커야하는 조건
					if((p[i].btime-(p[j].ctime-p[i].ctime))>p[j].btime && nextArrival == 0){ 
						// p[i]의 실행시간-(p[j]의 도착시간 - p[i]의 도착시간)
						nextArrival=1; // 도착시간이 작은 프로세스가 여러개더라도 하나의 프로세스만 바꾸기위해 설정
						real_p[k].ctime = p[i].ctime; //바뀐 값을 새로운 배열에 저장
						real_p[k].btime = p[j].ctime-p[i].ctime;
						strcpy(real_p[k].p_name,p[i].p_name);
						real_p[k].wtime = p[i].wtime;
						
						n++; //프로세스의 수를 하나 증가시켜서 남은 실행시간과 바뀐 도착시간을 저장
						strcpy(p[n].p_name,p[i].p_name);
						p[n].btime = (p[i].btime-(p[j].ctime-p[i].ctime));
						p[n].ctime = p[j].ctime;
						p[n].wtime = p[i].wtime;
					
						p[i].btime = real_p[k].btime; //
						p[i].ctime = real_p[k].ctime;
						
						num = num+real_p[k].btime;
						k++;
						i++; //바뀌고 난후에 다음프로세스는 무조건 바로 저장하기 위해 설정
					}
				}
			}
		}
		if(count > 0){ //실행시간이 적은것이 잇을경우 프로세스의 자리를 바꾸기 위해 설정
				for(int q=i+1; q<i+1+count; q++){
					if(p[q].btime>p[q+1].btime && p[q+1].btime !=0) { //n번의도착시간이 n+1번보다 크면(늦으면) 
						temp=p[q].btime;
						temp1=p[q].ctime; 
						p[q].btime=p[q+1].btime;
						p[q].ctime=p[q+1].ctime;
						p[q+1].btime=temp;
						p[q+1].ctime=temp1;
						strcpy(c[q],p[q].p_name); 
						strcpy(p[q].p_name,p[q+1].p_name);
						strcpy(p[q+1].p_name,c[q]);
					}
				}
			}
		
		if(k==i){ //변경되지 않는 프로세스들에 한해서 새로운 배열에 저장.
			real_p[k].btime = p[i].btime;
			real_p[k].ctime = p[i].ctime;
			strcpy(real_p[k].p_name,p[i].p_name);
			real_p[k].wtime = p[i].wtime;
			num = num+real_p[k].btime; //num에 현재 실행값 저장.
			k++;
		}

		count = 0; //포문이 한번 끝나면 카운트 초기화
		nextArrival = 0;
	}
		
	for(int i=1;i<=n;i++){ //출력을 위해 새로만든 프로세스의 내용을 p[n]에 저장.
		p[i].btime = real_p[i].btime;
		p[i].ctime = real_p[i].ctime;
		strcpy(p[i].p_name, real_p[i].p_name);
		p[i].wtime = real_p[i].wtime;
	}
	Calculate(); 
	Gantt_chart();

}
//R_R Algorithm
void R_R(){
	int n1=1, k=1,num=0, count=0, temp, temp1; 
	int T_q =0; // Time quantum 값 저장.
	p_inform real_p[20]; //실제 정렬될 프로세스들을 저장하는 구조체배열
	p_inform p_array[10];//현재실행시간보다 도착시간이 작은 프로세스들을 저장하는 구조체 배열
	Twt=0; 
    Ttt=0; 
    
	printf("\n\n << Round-Robin ALGORITHM >>\n\n"); 
	printf(" Time Quantum 을 입력해 주세요. ");
	scanf("%d",&T_q);
	
	sortProcess(); //프로세스를 도착시간 순서대로 정렬
	
	for(int i=1; i<=n; i++){ // 비교를 위해 모든 배열 0 으로 초기화
		p_array[i].btime=0;
		p_array[i].ctime=0;
	}
	for(int i=1; i<=n;i++){
		for(int j=i; j<=n; j++){
			if(p[j].ctime<=num){ //프로세스를 j부터 순서대로 현재 시간값과 비교하여 현재시간보다 도착시간이 작으면 p_array배열에 저장
				p_array[k].btime = p[j].btime;
				p_array[k].ctime = p[j].ctime;
				strcpy(p_array[k].p_name,p[j].p_name);
				p_array[k].wtime = p[j].wtime;
				k++;
			}
		}
		if(p_array[1].btime != 0){
			if(p_array[1].btime>T_q){ 
				//p_array배열에 값이 들어가있고 1번째배열의 실행시간이 T_q보다 클때
				real_p[i].btime=T_q; //실제배열에 T_q값 대입
				real_p[i].ctime=p_array[1].ctime; 
				strcpy(real_p[i].p_name,p_array[1].p_name);
				real_p[i].wtime=p_array[1].wtime;

				n++; //n을 하나 증가하여 Time quantum만큼 실행후 남은 실행시간과 도착시간을 증가된 p[n]에 저장. 
				p[n].btime=p_array[1].btime-T_q;
				p[n].ctime=num+T_q;//현재실행값에 Time quantum 을 추가한 값을 p[n]에 저장
				strcpy(p[n].p_name,p_array[1].p_name);
				p[n].wtime=p_array[1].wtime;

				p[i].btime=T_q;
				num+=real_p[i].btime;
				}
			else if(p_array[1].btime<=T_q){ 
				//p_array배열에 값이 들어있고 1번째 배열의 실행시간이 T_q보다 작거나 같을때
				real_p[i].btime=p_array[1].btime;
				real_p[i].ctime=p_array[1].ctime;
				strcpy(real_p[i].p_name,p_array[1].p_name);
				real_p[i].wtime=p_array[1].wtime;

				p[i].btime=T_q;
				num+=real_p[i].btime;
				}
		}
		else{ //p_array배열에 값이 없을때
			if(p[i].btime<=T_q){ //p[i]의 도착시간이 T_q보다 작거나 같을때
				real_p[i].btime=p[i].btime;
				real_p[i].ctime=p[i].ctime;
				real_p[i].wtime=p[i].wtime;
				strcpy(real_p[i].p_name,p[1].p_name);
				num+=real_p[i].btime;
			}
			else{ //p[i]의 도착시간이 T_q보다 클때
				real_p[i].btime=T_q;
				real_p[i].ctime=p[i].ctime;
				strcpy(real_p[i].p_name,p[i].p_name);
				real_p[i].wtime=p[i].wtime;

				n++; //n을 하나 증가하여 Time quantum만큼 실행후 남은 실행시간과 도착시간을 증가된 p[n]에 저장. 
				p[n].btime=p[i].btime-T_q;
				p[n].ctime=num+T_q;//현재실행값에 Time quantum 을 추가한 값을 p[n]에 저장
				strcpy(p[n].p_name,p[i].p_name);
				p[n].wtime=p[i].wtime;

				p[i].btime=T_q;
				num+=real_p[i].btime;
			}
		}
		
		for(int j=n;j>i; j--){ //배열에들어있는 프로세스들을 뒤에서 부터 정렬 실행시간이 작을경우 앞으로 이동.
			if(p[j].ctime<p[j-1].ctime){
					temp=p[j-1].btime;
					temp1=p[j-1].ctime;
					p[j-1].btime=p[j].btime;
					p[j-1].ctime=p[j].ctime;
					p[j].btime=temp;
					p[j].ctime=temp1;
					strcpy(c[i],p[j-1].p_name); 
					strcpy(p[j-1].p_name,p[j].p_name);
					strcpy(p[j].p_name,c[i]);
			}
		}
		k=1; //k를 1로 초기화
	}
	for(int i=1;i<=n;i++){ //출력을 위해 새로만든 프로세스의 내용을 p[n]에 저장.
		p[i].btime = real_p[i].btime;
		p[i].ctime = real_p[i].ctime;
		strcpy(p[i].p_name, real_p[i].p_name);
		p[i].wtime = real_p[i].wtime;
	}

	Calculate(); 
	Gantt_chart();
}

//sort Algorithm
void sortProcess() //배열을 정렬하기 위한 알고리즘. 
{ 
    int i,j,temp, temp1; 
	
    for(i=1;i<=n;i++) { 
        for(j=i+1;j<=n;j++) { 
			if(p[i].ctime>p[j].ctime) { //n번의도착시간이 n+1번보다 크면(늦으면) 
				temp=p[i].btime;
				temp1=p[i].ctime;
				p[i].btime=p[j].btime;
				p[i].ctime=p[j].ctime; 
				p[j].btime=temp;
				p[j].ctime=temp1;
				strcpy(c[i],p[i].p_name); 
				strcpy(p[i].p_name,p[j].p_name);
				strcpy(p[j].p_name,c[i]);
            } 
        } 
    } 

} 
