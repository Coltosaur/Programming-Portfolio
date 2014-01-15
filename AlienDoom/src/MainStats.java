/*
 * Author@ Colt Campbell
 */

public class MainStats
{
	private int uHp, uIHp, uStr, uiStr, uAgil, uEdnce, uInv, uiInv, aIatk, aHp, aIHp, aAtk, uDef,iDef, aDef, aiDef,
		aAgil, aiAgil;

	public MainStats()
	{
		uHp = 0;
		uIHp = 0;
		uStr = 0;
		uiStr = 0;
		uAgil = 0;
		uEdnce = 0;
		uInv = 0;
		uiInv = 0;
		aHp = 0;
		aIHp = 0;
		aAtk = 0;
		aIatk = 0;
		uDef = 0;
		iDef = 0;
		aDef = 0;
		aiDef = 0;
		aAgil = 0;
		aiAgil = 0;
	}

	public MainStats(int hp, int ihp, int agil, int ednce, int str,int istr, int def,int idef, int inv, int iinv)
	{
		uHp = hp;
		uIHp = ihp;
		uStr = str;
		uiStr = istr;
		uAgil = agil;
		uEdnce = ednce;
		uDef = def;
		iDef = idef;
		uInv = inv;
		uiInv = iinv;
	}

	public MainStats(int ehp,int eihp, int eatk, int ieatk, int adef, int aidef, int egil, int eigil)
	{
		aHp = ehp;
		aIHp = eihp;
		aAtk = eatk;
		aIatk = ieatk;
		aDef = adef;
		aiDef = aidef;
		aAgil = egil;
		aiAgil = eigil;
	}

	public void setHp(int newValue)
	{
		uHp = newValue;
	}
	public int getHp()
	{
		return uHp;
	}

	public void setIHp(int newValue2)
	{
		uIHp = newValue2;
	}
	public int getIHp()
	{
		return uIHp;
	}

	public void setEdnce(int newValue3)
	{
		uEdnce = newValue3;
	}
	public int getEdnce()
	{
		return uEdnce;
	}

	public void setStr(int newValue8)
	{
		uStr = newValue8;
	}
	public int getStr()
	{
		return uStr;
	}
	
	public void setIStr(int newValue18)
	{
		uiStr = newValue18;
	}
	public int getIStr()
	{
		return uiStr;
	}

	public void setAgil(int newValue9)
	{
		uAgil = newValue9;
	}
	public int getAgil()
	{
		return uAgil;
	}

	public void setEhp(int newValue4)
	{
		aHp = newValue4;
	}
	public int getEhp()
	{
		return aHp;
	}

	public void setEIhp(int newValue5)
	{
		aIHp = newValue5;
	}
	public int getEIhp()
	{
		return aIHp;
	}

	public void setEatk(int newValue6)
	{
		aAtk = newValue6;
	}
	public int getEatk()
	{
		return aAtk;
	}

	public void setEiatk(int newValue7)
	{
		aIatk = newValue7;
	}
	public int getEiatk()
	{
		return aIatk;
	}

	//also defense will need to be added eventually too, it will be set up the way attack is now
	public void setEdef(int newValue13)
	{
		aDef = newValue13;
	}
	public int getEdef()
	{
		return aDef;
	}
	
	public void setEidef(int newValue15)
	{
		aiDef = newValue15;
	}
	public int getEidef()
	{
		return aiDef;
	}
	
	public void setEAgil(int newValue19)
	{
		aAgil = newValue19;
	}
	public int getEAgil()
	{
		return aAgil;
	}
	public void setEiAgil(int newValue20)
	{
		aiAgil = newValue20;
	}
	public int getEiAgil()
	{
		return aiAgil;
	}
	
	public void setDef(int newValue14)
	{
		uDef = newValue14;
	}
	public int getDef()
	{
		return uDef;
	}
	public void setIDef(int newValue21)
	{
		iDef = newValue21;
	}
	public int getIDef()
	{
		return iDef;
	}
	
	public void setInv(int newValue16)
	{
		uInv = newValue16;
	}
	public int getInv()
	{
		return uInv;
	}
	
	public void setIinv(int newValue17)
	{
		uiInv = newValue17;
	}
	public int getIinv()
	{
		return uiInv;
	}
}