while(mask<(1<<n))
{//枚举大小为i的集合
	int x=mask&-mask,y=mask+x;
	int p=mask;
	do
	{//枚举包含最低位的mask的子集p
		if ((p & x) >0)//保证该子集不被任何一个子集包含
		/*
		...
		*/
		p=(p-1)&(mask);
	}while (p!=mask);
	mask=((mask & ~y)/x >>1)|y;
}