#include <stdio.h>
// int Testcase,submission;
// int score;
// int hold;

// int main() {
//     scanf("%d",&Testcase);
//     for(int i=0;i<Testcase;i++){
//         scanf("%d",&submission);
//         int a[submission],b[submission];
//         printf("Testcase%d t%d\n",Testcase,submission);
//         for(int j=0;j<submission;j++){
//             scanf("%d",&a[j]);
//             scanf("%d",&b[j]);
//         }
//         for(int d=0;d<submission;d++){
//             for(int c=d+1;c<submission;c++){
//                 if(a[c]<a[d]){
//                     hold=a[d];
//                     a[d]=a[c];
//                     a[c]=hold;
//                     hold=b[d];
//                     b[d]=b[c];
//                     b[c]=hold;
//                 }
//             }
//         }
//         for(int i=0;i<submission;i++)printf("%d %d\n",a[i],b[i]);
//         printf("\n");
//         int occurance[8]={0};
//         for (int i = 0; i < submission; i++)
//         {
//             if(a[i]<9){
//                 if(a[i]==a[i+1]){
//                     score+=(b[i]>b[i+1])?b[i]-b[i+1]:b[i+1]-b[i];
//                     occurance[a[i]]++;
//                 }
//                 if(occurance[a[i]]==0)score+=b[i];
//             }
//             printf("%d\n",score);
//         }
//         printf("%d\n",score);
//         score=0;
//     }
// 	return 0;
// }

int main() {
    int tc,submissions;
	scanf("%d",&tc);
	printf("tc:%d\n",tc);
	for(int i=0;i<tc;i++){
	    int sum=0;
	scanf("%d",&submissions);
	printf("sub:%d\n",submissions);
    int p_i[submissions],s_i[submissions],score[8]={0};
	    for(int j=0;j<submissions;j++){
	        scanf("%d",&p_i[j]);
	        scanf("%d",&s_i[j]);
	       printf("p:%d s:%d\n",p_i[j],s_i[j]);
	        if(p_i[j]<9&&p_i[j]>0){
	            if(score[p_i[j]]==0)score[p_i[j]]+=s_i[j];
	            else if(score[p_i[j]]<s_i[j]){
	                score[p_i[j]]=s_i[j];
	            }
	        }
	    }
	    for(int temp=0;temp<9;temp++){
	       printf("%d:%d\n",temp,score[temp]);
	        sum+=score[temp];
	    }
	   printf("%d\n",sum);
	}
	return 0;
}