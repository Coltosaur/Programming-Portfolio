/**
 * @(#)AlienDoom.java
 *
 * AlienDoom application
 *
 * @Colt Campbell
 * @Updated version 2.00 2012/8/8
 * @version 1.00 2011/1/4
 */

public class AlienDoom {

    public static void main(String[] args) {

    	final AlienControl runner = new AlienControl();

		javax.swing.SwingUtilities.invokeLater(new Runnable() {
                        @Override
			public void run() {
				runner.generateMainMenuGUI(); 
			}
		});

    }
}
