/*
 * Author@ Colt Campbell
 */
import java.util.Random;


public class Aliens extends MainStats
{
	private int experience, crystals, aProbability, initprob;

	private String alientype;

	public Aliens()
	{
		alientype = "";
	}

	public Aliens(int ehp, int eihp, int eatk, int ieatk, int aprob, int aIni, int adef, int aidef, int egil, int eigil, int exp, int crys)
	{
		super(ehp, eihp, eatk, ieatk, adef, aidef, egil,eigil);
		aProbability = aprob;
		initprob = aIni;
                experience = exp;
                crystals = crys; 
	}
	
	public void setAprob(int newValue11)
	{
		aProbability = newValue11;
	}
	public int getAprob()
	{
		return aProbability;
	}
	public void setAiprob(int newValue12)
	{
		initprob = newValue12;
	}
	public int getAiprob()
	{
		return initprob;
	}

	public void setExp(int exp)
	{
		experience = exp;
	}
	public int getExp()
	{
		return experience;
	}
        
        public void setAlienType(String s)
        {
            alientype = s;
        }
        public String getAlienType()
        {
            return alientype;
        }
        
	public void setAnyExp()
	{
		Random generator = new Random();

		if (alientype.equals("zorg"))
		{
			setExp(getExp() + generator.nextInt(10)+1);
		}
		if (alientype.equals("zarvox"))
		{
			setExp(getExp() + generator.nextInt(200)+11);
		}
		if (alientype.equals("zirvex"))
		{
			setExp(getExp() + generator.nextInt(500)+201);
		}
		if (alientype.equals("zarkonaut"))
		{
			setExp(getExp() + generator.nextInt(1000)+501);
		}
		if (alientype.equals("zekorov"))
		{
			setExp(getExp() + generator.nextInt(1000000)+500001);
		}
	}

	public void setCrystals(int crys)
	{
		crystals = crys;
	}
	public int getCrystals()
	{
		return crystals;
	}
	public void setAnyCrys()
	{
		Random generator = new Random();

		if (alientype.equals("zorg"))
		{
			setCrystals(getCrystals() + generator.nextInt(200)+1);
		}
		if (alientype.equals("zarvox"))
		{
			setCrystals(getCrystals() + generator.nextInt(300)+201);
		}
		if (alientype.equals("zirvex"))
		{
			setCrystals(getCrystals() + generator.nextInt(500)+101);
		}
		if (alientype.equals("zarkonaut"))
		{
			setCrystals(getCrystals() + generator.nextInt(4000)+1001);
		}
		if (alientype.equals("zekorov"))
		{
			setCrystals(getCrystals() + generator.nextInt(100000)+50001);
		}
	}

	public void getAtype()
	{

		//have to make initial value for EAgil :P 
		if(alientype.equals("zorg"))
		{
			setEhp(getEIhp() - 5);
			setEatk(getEiatk() - 2);
			setAprob(getAiprob() - 1);
			setEdef(getEidef() - 3);
			setEAgil(getEiAgil() - 5);
		}
		if(alientype.equals("zarvox"))
		{
			setEhp(getEIhp() + 75);
			setEatk(getEiatk() + 70);
			setAprob(getAiprob() + 10);
			setEdef(getEidef() + 50);
			setEAgil(getEiAgil() + 70);
		}
		if(alientype.equals("zirvex"))
		{
			setEhp(getEIhp() + 600);
			setEatk(getEiatk() + 350);
			setAprob(getAiprob() + 100);
			setEdef(getEidef() + 200);
			setEAgil(getEiAgil() + 400);
		}
		if(alientype.equals("zarkonaut"))
		{
			setEhp(getEIhp() + 1500);
			setEatk(getEiatk() + 1000);
			setAprob(getAiprob() + 500);
			setEdef(getEidef() + 700);
			setEAgil(getEiAgil() + 1250);
		}
		if(alientype.equals("zekorov"))
		{
			setEhp(getEIhp() + 100000);
			setEatk(getEiatk() + 75000);
			setAprob(getAiprob() + 500000);
			setEdef(getEidef() + 60000);
			setEAgil(getEiAgil() + 200000);
		}
	}

        @Override
	public String toString()
	{
            return alientype;
	}
}