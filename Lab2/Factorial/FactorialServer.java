package Lab2.Factorial;

import java.rmi.Naming;

public class FactorialServer {
     // Constructor
    public FactorialServer()
    {
        try {
            // Create a object reference for the interface
            Factorial c = new FactorialImpl();
  
            // Bind the localhost with the service
            Naming.rebind("rmi://localhost:1099/FactorialService", c);
        }
        catch (Exception e) {
            // print the error
            System.out.println("ERR: " + e);
        }
    }
  
    public static void main(String[] args)
    {
        new FactorialServer();
    }
    
}
