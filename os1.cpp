/* �ü�� �����ٸ� �˰��� ���α׷���(2014/11/29)
 * 201158062 �۽���
 * c�� Ȱ���� ���� ���μ����� ���μ��� �����ٸ� �˰����� 4�ܰ迡 ���� ������ ���α׷�
 */

#include<stdio.h> 
#include<conio.h> 
#include<string.h> 

int n,Bu[20],Twt,Ttt,A[20],Wt[20],w;
float Awt,Att;
char pname[20][20],c[20][20];

struct p_inform{ //���μ����� �̸�, �����ð�,����ð�,���ð��� ����ü�� �������.
	char p_name[20];	//���μ����̸�
	int ctime;			//�����ð�
	int btime;			//����ð�
	int wtime;			//���ð�
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
		printf("\n  		****** �˰��� ���� ******\n\n");
		printf("1)FCFS		2)SJF		3)SRTF		4)R_R \n\n");
		printf("==================================================================\n");
		printf("\n\n<< ���Ͻô� �����ٸ� �˰����� �����ϼ��� >>\n");
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
				printf("���� ��ȣ�� �����ϼ̽��ϴ�.\n");
				break;
		}
		printf("\n\n\n");
	}

}

void Getdata() 
{ 
	printf("\n*** ��� ���μ����� ����ڽ��ϱ� : "); 
	scanf("%d",&n); 

	 for(int i=1;i<=n;i++) { 
		fflush(stdin); 
		printf("\n\n * ���μ����̸��� �Է��ϼ��� : ");  
		scanf("%s",&p[i].p_name);
		
		printf("*  %s�� �����ð��� �Է��ϼ��� =  ",p[i].p_name); 
		scanf("%d",&p[i].ctime); 
		
		printf("*  %s�� ����ð��� �Է��ϼ���  = ",p[i].p_name); 
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
			if(p[i].ctime>p[j].ctime) { //n���ǵ����ð��� n+1������ ũ��(������) 
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
			if(num>p[j].ctime){ //num�� p[j]�� �����ð����� �� ũ��
				if(p[j].btime>p[j+1].btime){ // p[j]�� ����ð��� p[j+1]�� ����ð����� ũ�� ��ü
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
		num+=p[n1].btime; // 0��° ���Ŀ��� i+1��° ���μ��������ð��� i�� ����ð����� ������ ���ϱ�.
	}
   Calculate(); 
   Gantt_chart();
}

//SRTF Algorithm
void SRTF(){
	int n1=1, k=1,num=0, count=0, temp, temp1;
	int nextArrival=0;//�����ð��� ��������ð����� ���� ���μ������߿� �ϳ��� �������ϱ� ���� ���� ����
	p_inform real_p[15];
	Twt=0; 
    Ttt=0; 
    
	printf("\n\n << SHORTEST REMAINING TIME FIRST ALGORITHM >>\n\n"); 
	
	sortProcess();
	
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			if(num>=p[j-1].ctime){ //���� ����ð����� �����ð��� ���� ���
				count++; //�����ð��� ���� ���μ������� �����ϱ� ���� ī��Ʈ.
				if(p[j].ctime-p[i].ctime>0){ //p[j]�� �����ð� - p[i]�� �����ð��� 0���� Ŀ���ϴ� ����
					if((p[i].btime-(p[j].ctime-p[i].ctime))>p[j].btime && nextArrival == 0){ 
						// p[i]�� ����ð�-(p[j]�� �����ð� - p[i]�� �����ð�)
						nextArrival=1; // �����ð��� ���� ���μ����� ���������� �ϳ��� ���μ����� �ٲٱ����� ����
						real_p[k].ctime = p[i].ctime; //�ٲ� ���� ���ο� �迭�� ����
						real_p[k].btime = p[j].ctime-p[i].ctime;
						strcpy(real_p[k].p_name,p[i].p_name);
						real_p[k].wtime = p[i].wtime;
						
						n++; //���μ����� ���� �ϳ� �������Ѽ� ���� ����ð��� �ٲ� �����ð��� ����
						strcpy(p[n].p_name,p[i].p_name);
						p[n].btime = (p[i].btime-(p[j].ctime-p[i].ctime));
						p[n].ctime = p[j].ctime;
						p[n].wtime = p[i].wtime;
					
						p[i].btime = real_p[k].btime; //
						p[i].ctime = real_p[k].ctime;
						
						num = num+real_p[k].btime;
						k++;
						i++; //�ٲ�� ���Ŀ� �������μ����� ������ �ٷ� �����ϱ� ���� ����
					}
				}
			}
		}
		if(count > 0){ //����ð��� �������� ������� ���μ����� �ڸ��� �ٲٱ� ���� ����
				for(int q=i+1; q<i+1+count; q++){
					if(p[q].btime>p[q+1].btime && p[q+1].btime !=0) { //n���ǵ����ð��� n+1������ ũ��(������) 
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
		
		if(k==i){ //������� �ʴ� ���μ����鿡 ���ؼ� ���ο� �迭�� ����.
			real_p[k].btime = p[i].btime;
			real_p[k].ctime = p[i].ctime;
			strcpy(real_p[k].p_name,p[i].p_name);
			real_p[k].wtime = p[i].wtime;
			num = num+real_p[k].btime; //num�� ���� ���ప ����.
			k++;
		}

		count = 0; //������ �ѹ� ������ ī��Ʈ �ʱ�ȭ
		nextArrival = 0;
	}
		
	for(int i=1;i<=n;i++){ //����� ���� ���θ��� ���μ����� ������ p[n]�� ����.
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
	int T_q =0; // Time quantum �� ����.
	p_inform real_p[20]; //���� ���ĵ� ���μ������� �����ϴ� ����ü�迭
	p_inform p_array[10];//�������ð����� �����ð��� ���� ���μ������� �����ϴ� ����ü �迭
	Twt=0; 
    Ttt=0; 
    
	printf("\n\n << Round-Robin ALGORITHM >>\n\n"); 
	printf(" Time Quantum �� �Է��� �ּ���. ");
	scanf("%d",&T_q);
	
	sortProcess(); //���μ����� �����ð� ������� ����
	
	for(int i=1; i<=n; i++){ // �񱳸� ���� ��� �迭 0 ���� �ʱ�ȭ
		p_array[i].btime=0;
		p_array[i].ctime=0;
	}
	for(int i=1; i<=n;i++){
		for(int j=i; j<=n; j++){
			if(p[j].ctime<=num){ //���μ����� j���� ������� ���� �ð����� ���Ͽ� ����ð����� �����ð��� ������ p_array�迭�� ����
				p_array[k].btime = p[j].btime;
				p_array[k].ctime = p[j].ctime;
				strcpy(p_array[k].p_name,p[j].p_name);
				p_array[k].wtime = p[j].wtime;
				k++;
			}
		}
		if(p_array[1].btime != 0){
			if(p_array[1].btime>T_q){ 
				//p_array�迭�� ���� ���ְ� 1��°�迭�� ����ð��� T_q���� Ŭ��
				real_p[i].btime=T_q; //�����迭�� T_q�� ����
				real_p[i].ctime=p_array[1].ctime; 
				strcpy(real_p[i].p_name,p_array[1].p_name);
				real_p[i].wtime=p_array[1].wtime;

				n++; //n�� �ϳ� �����Ͽ� Time quantum��ŭ ������ ���� ����ð��� �����ð��� ������ p[n]�� ����. 
				p[n].btime=p_array[1].btime-T_q;
				p[n].ctime=num+T_q;//������ప�� Time quantum �� �߰��� ���� p[n]�� ����
				strcpy(p[n].p_name,p_array[1].p_name);
				p[n].wtime=p_array[1].wtime;

				p[i].btime=T_q;
				num+=real_p[i].btime;
				}
			else if(p_array[1].btime<=T_q){ 
				//p_array�迭�� ���� ����ְ� 1��° �迭�� ����ð��� T_q���� �۰ų� ������
				real_p[i].btime=p_array[1].btime;
				real_p[i].ctime=p_array[1].ctime;
				strcpy(real_p[i].p_name,p_array[1].p_name);
				real_p[i].wtime=p_array[1].wtime;

				p[i].btime=T_q;
				num+=real_p[i].btime;
				}
		}
		else{ //p_array�迭�� ���� ������
			if(p[i].btime<=T_q){ //p[i]�� �����ð��� T_q���� �۰ų� ������
				real_p[i].btime=p[i].btime;
				real_p[i].ctime=p[i].ctime;
				real_p[i].wtime=p[i].wtime;
				strcpy(real_p[i].p_name,p[1].p_name);
				num+=real_p[i].btime;
			}
			else{ //p[i]�� �����ð��� T_q���� Ŭ��
				real_p[i].btime=T_q;
				real_p[i].ctime=p[i].ctime;
				strcpy(real_p[i].p_name,p[i].p_name);
				real_p[i].wtime=p[i].wtime;

				n++; //n�� �ϳ� �����Ͽ� Time quantum��ŭ ������ ���� ����ð��� �����ð��� ������ p[n]�� ����. 
				p[n].btime=p[i].btime-T_q;
				p[n].ctime=num+T_q;//������ప�� Time quantum �� �߰��� ���� p[n]�� ����
				strcpy(p[n].p_name,p[i].p_name);
				p[n].wtime=p[i].wtime;

				p[i].btime=T_q;
				num+=real_p[i].btime;
			}
		}
		
		for(int j=n;j>i; j--){ //�迭������ִ� ���μ������� �ڿ��� ���� ���� ����ð��� ������� ������ �̵�.
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
		k=1; //k�� 1�� �ʱ�ȭ
	}
	for(int i=1;i<=n;i++){ //����� ���� ���θ��� ���μ����� ������ p[n]�� ����.
		p[i].btime = real_p[i].btime;
		p[i].ctime = real_p[i].ctime;
		strcpy(p[i].p_name, real_p[i].p_name);
		p[i].wtime = real_p[i].wtime;
	}

	Calculate(); 
	Gantt_chart();
}

//sort Algorithm
void sortProcess() //�迭�� �����ϱ� ���� �˰���. 
{ 
    int i,j,temp, temp1; 
	
    for(i=1;i<=n;i++) { 
        for(j=i+1;j<=n;j++) { 
			if(p[i].ctime>p[j].ctime) { //n���ǵ����ð��� n+1������ ũ��(������) 
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
