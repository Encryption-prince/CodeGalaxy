import java.util.Scanner;

public class reverseStr {
    public static void main(String[] args) {
        String str = new String();
        String temp = new String();
        String rev = new String();
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a String : ");
        str = sc.nextLine();
        str = " " + str;
        for (int i = str.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(str.charAt(i)))
                temp = str.charAt(i) + temp;
            else {
                rev = rev + temp + " ";
                temp = "";
            }

        }
        System.out.println("Original String : " + str);
        System.out.println("Reversed String : " + rev);
        sc.close();
    }
}