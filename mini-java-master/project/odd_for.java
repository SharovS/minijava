class Factorial {
public static void main(String[] a) {
    System.out.println(new Fac().ComputeFac(0, 100));
}
}
class Fac {
    public int ComputeFac(int from, int to) {
    	int res;
        for(; true;){
        	res = from - from / 2 * 2;
        	if ( 0 < res )
        		res = res;
        	else
        		System.out.println( from );
        	from++;
        }
        return res;
    }
}