import java.util.Scanner;

public class HW {

    public static void main(String[] args) {
        System.out.println("please enter a string or a number:");
        Scanner scanner = new Scanner(System.in);
        while(scanner.hasNext()){
            String ss=scanner.nextLine();
            String sa="";
            for(int j=0;j<ss.length();j++){
                sa=ss.substring(j, j+1)+sa;
            }
            if(ss.equals(sa)){
                System.out.println("Yes, it's a palindrome");
            }else{
                System.out.println("It's not a palindrome");
            }
        }
        scanner.close();

    }

}