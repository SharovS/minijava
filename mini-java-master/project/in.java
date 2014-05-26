class Factorial {
public static void main(String[] a) {
    System.out.println(new Fac().ComputeFac(0, 100));
}
}
class Fac {
    public int ComputeFac(int from, int to) {
		int res1;
    	int res = 0;
		res1 = res++;
        for(res = 1; true;){
        	res = from - from / 2 * 2;
        	if ( 0 < res )
        		res = res - 2;
        	else
        		System.out.println( from );
        }
		System.out.println("hola");
        return res1;
    }
}