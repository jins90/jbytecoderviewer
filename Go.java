import java.util.*;

public class Go
{
    public int x = 10;
    private int j = 5;
    Integer k = null;
    Map<String, String> m = new HashMap<String, String>();

    public Go()
    {
        x = 50;
    }

    public void hello(int j, int k) {
        String name = "HELLO";
        x = 30;
        x = x + 5;
        j = 10;
        k = 50;
        System.out.println(k);
    }
 
    public static void main(String args[])
    {
       Go g = new Go();
       g.hello(20, 30);
    }
}
