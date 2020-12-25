import java.util.*;

class Main {
    static int maxpoly=101;//행렬의 최대 갯수

    //메인함수
    public static void main(String[] args) {
        polynomial [] poly1;
        polynomial [] poly2;
        polynomial [] result;//결과값이다.

        poly1=Zero();//초기화
        System.out.println("첫번째 다항식을 입력하세요. (지수는 100이하)");
        poly1=Getnumbers(poly1);//사용자로 부터 입력을 받음

        poly2=Zero();//초기화
        System.out.println("두번째 다항식을 입력하세요. (지수는 100이하)");
        poly2=Getnumbers(poly2);//사용자로 부터 입력을 받음

        result=Add(poly1,poly2);//더하기 연산
        PrintPoly(result);//결과 값 출력
    }

    //Polynomial ADT
    //initialize polynomial
    static polynomial [] Zero()
    {
        polynomial [] poly;
        poly = new polynomial [maxpoly];

        for(int i=0;i<maxpoly;i++)
        {
            poly [i]=new polynomial();
        }
        return poly;
    }

    //Polynomial ADT
    //다항식에 항을 추가한다.
    static polynomial [] Attach(polynomial [] poly, float coef, int expon)
    {
        int length =Getlength(poly);

        if(coef==0){
            System.out.println("계수가 0인 경우는 무의미 합니다.");
            System.exit(1);
        }

        //중복되는 항은 exception처리
        for (int i=0;i<length;i++){
            if(poly[i].exponential==expon){
                System.out.println("지수가 중복되는 항이 있습니다.");
                System.exit(1);
            }

        }

        //항을 추가한다.
        poly[length].coefficient=coef;
        poly[length].exponential=expon;

        //순서에 맞게 항을 추가한다.
        poly=SortPolynomial(poly);

        return poly;
    }

    //Polynomial ADT
    //다항식을 더하는 함수이다.
    static polynomial [] Add(polynomial [] poly1, polynomial [] poly2)
    {
        int length1 =Getlength(poly1);
        int current1=0;
        int length2 =Getlength(poly2);
        int current2=0;

        polynomial [] poly;
        poly=Zero();

        while(current1<length1&&current2<length2){
        if(poly1[current1].exponential>poly2[current2].exponential){//poly1의 계수가 poly2의 계수보다 큰 경우
            poly=Attach(poly,poly1[current1].coefficient,poly1[current1].exponential);
            current1++;
        }
        else if(poly1[current1].exponential<poly2[current2].exponential){//poly1의 계수가 poly2의 계수보다 작은 경우
            poly=Attach(poly,poly2[current2].coefficient,poly2[current2].exponential);
            current2++;
        }
        else{//poly1의 계수와 poly2의 계수가 같은 경우
            float coef;
            coef=poly1[current1].coefficient+poly2[current2].coefficient;

            if(coef!=0){
                poly=Attach(poly,coef,poly2[current2].exponential);
                current1++;
                current2++;
            }
            else{
                current1++;
                current2++;
            }
        }
    }
        while(current1<length1){
            poly=Attach(poly,poly1[current1].coefficient,poly1[current1].exponential);
            current1++;
        }
        while(current2<length2){
            poly=Attach(poly,poly2[current2].coefficient,poly2[current2].exponential);
            current2++;
        }

        return poly;
    }

    //다항식의 항의 갯수를 반환하는 함수이다.
    static int Getlength(polynomial [] poly)
    {
        int length=0;

        while(length<maxpoly)
        {
            if(poly[length].exponential!=-1)
                length++;
            else
                break;
        }

        return length;
    }

    //사용자로부터 숫자를 입력받는 함수이다.
    static polynomial[] Getnumbers(polynomial [] poly)
    {
        Scanner sc = new Scanner(System.in);
        float coefficientInput=0;
        int exponentialInput=-1;
        int index=0;

        String input;
        input=sc.nextLine();

        String[] array_input = input.split(" ");

        if(array_input.length%2==1)
        {
            System.out.println("짝수개의 패어를 맞춰주세요.");
            System.exit(1);
        }

        //짝수번째는 계수, 홀수번째는 지수이다.
        for(index=0;index<array_input.length;index+=2){
            if(array_input[index]!="0"&&Integer.parseInt(array_input[index+1])>=0)
                poly=Attach(poly,Float.parseFloat(array_input[index]),Integer.parseInt(array_input[index+1]));
            else{
                System.out.println("지수,계수 입력조건이 맞지 않습니다.");
                System.exit(1);
            }
        }



        return poly;
    }

    //지수에 대하여 내림차순으로 정렬하는 함수이다.
    //버블소트를 사용하여 정렬한다.
    static polynomial [] SortPolynomial(polynomial [] poly)
    {
        int length = Getlength(poly);
        polynomial temp;

        for(int i=0;i<length;i++) {
            for (int j = 0; j < length - 1 - i; j++) {
                if (poly[j].exponential < poly[j + 1].exponential) {
                    temp = poly[j + 1];
                    poly[j + 1] = poly[j];
                    poly[j] = temp;
                }
            }
        }
        return poly;
    }

    //다항식을 출력하는 함수이다.
    static void PrintPoly(polynomial [] poly)
    {
        int length=Getlength(poly);
        for(int i=0;i<length;i++){
            if(i!=0){
                System.out.print(" + ");
            }
            System.out.print(poly[i].coefficient+"X^"+poly[i].exponential);
        }

    }
}

//polynomial의 객체이다.
class polynomial{
    int exponential=-1;
    float coefficient=0;
}



