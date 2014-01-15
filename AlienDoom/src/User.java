/*
 * Author@ Colt Campbell
 */

public class User extends MainStats
{
	private int level, probability;

	public User()
	{
		level = 0;
		probability = 0;
	}

	public User(int hp, int ihp, int str,int istr, int agil, int ednce, int lvl, int prob, int def,int idef, int inv, int iinv)
	{
		super(hp,ihp, agil, ednce, str,istr, def,idef, inv, iinv);
		level = lvl;
		probability = prob;
	}

	public void setProb(int newValue10)
	{
		probability = newValue10;
	}
	public int getProb()
	{
		return probability;
	}

	public void lvlUp()
	{
		level += 1;

		setHp(getIHp() + 20);
		setIHp(getHp());

		setStr(getStr() + 8);
		setIStr(getIStr() + 8);
		setAgil(getAgil() + 8);
		setEdnce(getEdnce() + 8);
		setProb(getProb() + 1);
		setDef(getDef() + 6);
		setIDef(getIDef() + 6);

		if(getIinv() < 20)
		{

			setIinv(getIinv() + 1);
			setInv(getInv() + 1);
		}
	}
	public int getLvl()
	{
		return level;
	}
	public void setLvl(int lvl)
	{
		level = lvl;
	}
}