package Lab2.Factorial;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;


public class FactorialClient {
	public static void main(String[] args)
	{

		try {
			// Create an remote object with the same name
			//and cast the lookup result to the interface
			Factorial c = (Factorial)
			Naming.lookup("rmi://localhost:1099/FactorialService");
			
			// take input number from user to calculate factorial
			Scanner scanner = new Scanner(System.in);
            System.out.print("Enter number to calculate Factorial: ");
            int num = scanner.nextInt();
			scanner.close();
			
			// Call the method for the results
			System.out.println("Factorial of "+ num +"= "+c.fact(num));
		}

		// If any error occur
		catch (MalformedURLException murle) {
			System.out.println("\nMalformedURLException: "
							+ murle);
		}

		catch (RemoteException re) {
			System.out.println("\nRemoteException: "
							+ re);
		}

		catch (NotBoundException nbe) {
			System.out.println("\nNotBoundException: "
							+ nbe);
		}

		catch (java.lang.ArithmeticException ae) {
			System.out.println("\nArithmeticException: " + ae);
		}
	}
}

