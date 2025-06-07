class Fact{
    public static void main(String[] args) {
        int n = 5,fact=1;
        for (int i=0; i<n;i++){
            fact*=i+1;
        }
        System.err.println(fact);
    }
}