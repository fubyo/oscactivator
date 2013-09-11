#include "TermManager.h"
#include "RulesPanelComponent.h"

TermManager::TermManager(void)
{
	min = 0;
	max = 1;
}

TermManager::~TermManager(void)
{

}

void TermManager::setMin(double Min)
{
	if (Min<min)
	{
		if (terms.size())
		{
			if (terms[0]->membership(min)==0)
			{
				terms[0]->setA(Min);
			}
			else
			{
				terms[0]->setA(Min);
				terms[0]->setB(Min);
			}
		}
		
	}
	else if (Min>min && Min<max)
	{
		int indexOfOtherTerm = getIndex(Min);

		for (int i = 0; i<indexOfOtherTerm; i++)  //remove terms inbetween
		{
			terms.remove(0);
		}

		if (terms.size())
		{
			if (Min>=terms[0]->a() && Min<terms[0]->b())
			{
				terms[0]->setA(Min);
			}
			else if (Min>=terms[0]->b() && Min<terms[0]->c())
			{
				terms[0]->setA(Min);
				terms[0]->setB(Min);
			}
			else if (Min>=terms[0]->c())
			{
				terms[0]->setA(Min);
				terms[0]->setB(Min);
				terms[0]->setC(Min);

				if (terms.size()>0)
					terms[1]->setA(Min);
			}
		}
	}
	
	min = Min;
}

void TermManager::setMax(double Max)
{
	if (Max>max)
	{
		if (terms.size()==1)
		{
			if (terms[0]->membership(max)==0)
			{
				terms[0]->setD(Max);
			}
			else
			{
				terms[0]->setC(Max);
				terms[0]->setD(Max);
			}
		}
		else if (terms.size())
		{
			terms[terms.size()-1]->setC(Max);
			terms[terms.size()-1]->setD(Max);
		}
	}
	else if (Max<max && Max>min)
	{
		int indexOfOtherTerm = getIndex(Max);

		int difference = terms.size()-1-indexOfOtherTerm;

		for (int i = 0; i<difference; i++)  //remove terms inbetween
		{
			terms.remove(indexOfOtherTerm+1);
		}
		
		int index = terms.size()-1;

		if (index>=0)
		{
			if (Max>=terms[index]->c() && Max<terms[index]->d())
			{
				terms[index]->setD(Max);
			}
			else if (Max>=terms[index]->b() && Max<terms[index]->c())
			{
				terms[index]->setD(Max);
				terms[index]->setC(Max);
			}
			else if (Max<terms[index]->b())
			{	
				terms[index]->setD(Max);
				terms[index]->setC(Max);
				terms[index]->setB(Max);

				if (index>0)
					terms[index-1]->setD(Max);
			}
		}
	}
	
	max = Max;
}

void TermManager::addTerm(String termName, double value)
{
	sortTerms();

	int index=getIndex(termName);

	if (index!=-1) //Term already there
	{
		if (index==0 && terms[index]->membership(min)) //First term
		{
			if ( value<terms[index]->b())
			{
				min = value;
				terms[index]->setA(value);
				terms[index]->setB(value);
			}
			else if (value>terms[index]->c() && (float)value<=terms[index]->d())
			{
				terms[index]->setC(value);
				if (terms.size()>1)
				{
					if( (float)value >= terms[index+1]->c())
					{
						double d = terms[index+1]->d();
						terms.remove(index+1);
						terms[index]->setD(d);
					}
					else if (value >= terms[index+1]->b())
					{
						terms[index+1]->setA(value);
						terms[index+1]->setB(terms[index+1]->c());
						terms[index]->setD(terms[index+1]->c());
					}
					else if (value >= terms[index+1]->a())
					{
						terms[index+1]->setA(value);
					}
				}
			}
			else if (value>terms[index]->b() && value<terms[index]->c())
			{
				terms[index]->setC(value);
				if (terms.size()>1)
					terms[index+1]->setA(value);
			}
			else if (value>terms[index]->d()) //outside of membership
			{
				if (terms.size()>1)
				{
					int indexOfOtherTerm = getIndex(value);
					int indexDifference = indexOfOtherTerm-index;

					for (int i = 0; i<indexDifference-1; i++)  //remove terms inbetween
					{
						terms.remove(index+1);
					}

					if (value>=terms[index+1]->a() && value<terms[index+1]->b())
					{
						terms[index]->setC(value);
						terms[index]->setD(terms[index+1]->b());
						terms[index+1]->setA(value);
					}
					else if (value>=terms[index+1]->b() && value<terms[index+1]->c())
					{
						terms[index]->setC(value);
						terms[index]->setD(terms[index+1]->c());
						terms[index+1]->setA(value);
						terms[index+1]->setB(terms[index+1]->c());
					}
					else if ((float)value>=terms[index+1]->c())
					{
						terms.remove(index+1);

						if (terms.size()>1)
						{
							terms[index]->setC(value);
							terms[index]->setD(terms[index+1]->b());
							terms[index+1]->setA(value);
						}
						else
						{
							if (value>max)
							{
								terms[index]->setC(value);
								terms[index]->setD(value);
								max = value;
							}
							else
							{
								terms[index]->setC(value);
								terms[index]->setD(max);
							}
						}
					}

				}
				else //no other terms
				{
					if (value>max)
					{
						terms[index]->setC(value);
						terms[index]->setD(value);
						max = value;
					}
					else
					{
						terms[index]->setC(value);
						terms[index]->setD(max);
					}
				}
			}
		}
		else if (index==terms.size()-1)  //Last term
		{
			if ( value>=terms[index]->d())
			{
				max = value;
				terms[index]->setC(value);
				terms[index]->setD(value);
			}
			else if (value>terms[index]->a() && value<=terms[index]->b())
			{
				terms[index]->setB(value);
				if (terms.size()>1)
					terms[index-1]->setD(value);
			}
			else if (value==terms[index]->a())
			{
				if (index>0)
				{
					terms[index-1]->setC(terms[index-1]->b());
					terms[index-1]->setD(value);
					terms[index]->setA(terms[index-1]->c());	
				}
				terms[index]->setB(value);
			}
			else if (value>terms[index]->b() && value<=terms[index]->c())
			{
				terms[index]->setB(value);
				if (index-1>=0)
					terms[index-1]->setD(value);
			}
			else if (value<terms[index]->a()) //outside of membership
			{
				if (terms.size()>1)
				{
					int indexOfOtherTerm = getIndex(value);
					int indexDifference = index-indexOfOtherTerm;

					for (int i = 0; i<indexDifference-1; i++)  //remove terms inbetween
					{
						terms.remove(index-indexDifference+1);
					}

					index = index-indexDifference+1;

					if ((float)value>terms[index-1]->c() && (float)value<terms[index-1]->d())
					{
						terms[index]->setB(value);
						terms[index]->setA(terms[index-1]->c());
						terms[index-1]->setD(value);
					}
					else if (value>terms[index-1]->b() && value<terms[index-1]->c())
					{
						terms[index]->setB(value);
						terms[index]->setA(terms[index-1]->b());
						terms[index-1]->setD(value);
						terms[index-1]->setC(terms[index-1]->b());
					}
					else if (value<=terms[index-1]->b())
					{
						terms.remove(index-1);
						index = index-1;

						if (terms.size()>1)
						{
							terms[index]->setB(value);
							terms[index]->setA(terms[index-1]->c());
							terms[index-1]->setD(value);
						}
						else
						{
							if (value<min)
							{
								terms[index]->setA(value);
								terms[index]->setB(value);
								min = value;
							}
							else
							{
								terms[index]->setB(value);
								terms[index]->setA(min);
							}
						}
					}

				}
				else //no other terms
				{
					if (value<min)
					{
						terms[index]->setA(value);
						terms[index]->setB(value);
						min = value;
					}
					else
					{
						terms[index]->setA(min);
						terms[index]->setB(value);
					}
				}
			}
		}
		else   // A term somewhere between other terms.	
		{
			int indexOfOtherTerm = getIndex(value);

			if (indexOfOtherTerm==index)
			{
				if (value<terms[index]->b())
				{
					terms[index]->setB(value);
					if (index!=0)
						terms[index-1]->setD(value);
				}
				else if (value>terms[index]->c())
				{
					terms[index]->setC(value);
					terms[index+1]->setA(value);
				}
				else if (value>terms[index]->b() && value<terms[index]->c())
				{
					double middleValue = (terms[index]->b()+terms[index]->c())/2;

					if (value>terms[index]->b() && value<middleValue)
					{
						terms[index]->setB(value);
						terms[index-1]->setD(value);
					}
					else if (value<terms[index]->c() && value>middleValue)
					{
						terms[index]->setC(value);
						terms[index+1]->setA(value);
					}
				}
			}
			else
			{
				int indexDifference = indexOfOtherTerm-index;
				bool leftExpansion = false;

				if (indexDifference>0)
				{
					for (int i = 0; i<indexDifference-1; i++)  //remove terms inbetween
					{
						terms.remove(index+1);
					}
				}
				else
				{
					for (int i = 0; i<abs(indexDifference)-1; i++)  //remove terms inbetween
					{
						terms.remove(index-abs(indexDifference)+1);
					}

					leftExpansion = true;
					index = index-abs(indexDifference)+1;
				}

				if (!leftExpansion)
				{
					if ((float)value>terms[index+1]->a() && (float)value<terms[index+1]->b())
					{
						terms[index]->setC(value);
						terms[index]->setD(terms[index+1]->b());
						terms[index+1]->setA(value);
					}
					else if ((float)value==terms[index+1]->b() && (float)value!=terms[index+1]->c())
					{
						terms[index+1]->setA(value);
						terms[index+1]->setB(terms[index+1]->c());

						terms[index]->setC(value);
						terms[index]->setD(terms[index+1]->b());
					}
					else if (value>terms[index+1]->b() && value<terms[index+1]->c())
					{
						terms[index]->setC(value);
						terms[index]->setD(terms[index+1]->c());
						terms[index+1]->setA(value);
						terms[index+1]->setB(terms[index+1]->c());
					}
					else if (value>=terms[index+1]->c())
					{
						terms.remove(index+1);

						if (terms.size()>1)
						{
							terms[index]->setC(value);

							if (index+1<=terms.size()-1)
							{
								terms[index]->setD(terms[index+1]->b());
								terms[index+1]->setA(value);
							}
							else
							{
								terms[index]->setD(value);
							}
						}
						else
						{
							if (value>max)
							{
								terms[index]->setC(value);
								terms[index]->setD(value);
								max = value;
							}
							else
							{
								terms[index]->setC(value);
								terms[index]->setD(max);
							}
						}
					}
				}
				else
				{
					if ((float)value == terms[index-1]->c() && (float)value != terms[index-1]->b())
					{
						terms[index-1]->setC(terms[index-1]->b());
						terms[index-1]->setD(value);

						terms[index]->setA(terms[index-1]->c());
						terms[index]->setB(value);
					}
					else if (value>terms[index-1]->c() && value<terms[index-1]->d())
					{
						terms[index]->setB(value);
						terms[index]->setA(terms[index-1]->c());
						terms[index-1]->setD(value);
					}
					else if (value>terms[index-1]->b() && value<terms[index-1]->c())
					{
						terms[index]->setB(value);
						terms[index]->setA(terms[index-1]->b());
						terms[index-1]->setD(value);
						terms[index-1]->setC(terms[index-1]->b());
					}
					else if (value<=terms[index-1]->b())
					{
						terms.remove(index-1);
						index = index-1;

						if (terms.size()>1)
						{
							terms[index]->setB(value);

							if (index>0)
							{
								terms[index]->setA(terms[index-1]->c());
								terms[index-1]->setD(value);
							}
							else if (index==0)
							{
								if (value<min)
									min=value;

								terms[index]->setA(min);
							}
						}
						else
						{
							if (value<min)
							{
								terms[index]->setA(value);
								terms[index]->setB(value);
								min = value;
							}
							else
							{
								terms[index]->setB(value);
								terms[index]->setA(min);
							}
						}
					}
				}
			}
		}
	}
	else if (index==-1) //Term not there
	{
		TrapezTerm* termAdded = 0;
		int indexOfNearestTerm = getIndex(value);

		if (indexOfNearestTerm==-1)  //No other term in array!
		{
			if (value<=min)
			{
				min = value;

				TrapezTerm* newTerm = new TrapezTerm();

				newTerm->setA(value);
				newTerm->setB(value);
				newTerm->setC(value);
				newTerm->setD(max);
				newTerm->setName(termName);

				terms.add(newTerm);
				termAdded = newTerm;
			}
			else if (value>min && value<max)
			{
				if (value<(min+max)/2)
				{
					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(min);
					newTerm->setB(min);
					newTerm->setC(value);
					newTerm->setD(max);
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else
				{
					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(min);
					newTerm->setB(value);
					newTerm->setC(max);
					newTerm->setD(max);
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
			}
			else 
			{
				max = value;

				TrapezTerm* newTerm = new TrapezTerm();

				newTerm->setA(min);
				newTerm->setB(value);
				newTerm->setC(value);
				newTerm->setD(value);
				newTerm->setName(termName);

				terms.add(newTerm);
				termAdded = newTerm;
			}
		}
		else if ((value>=terms[indexOfNearestTerm]->a() && value<= terms[indexOfNearestTerm]->b()) || value<min)
		{
			if (indexOfNearestTerm!=0) //nearest term not the first term
			{
				if ((float)value==terms[indexOfNearestTerm]->b() && (float)value==terms[indexOfNearestTerm]->c())
				{
					double a = terms[indexOfNearestTerm]->a();
					double b = terms[indexOfNearestTerm]->b();
					double c = terms[indexOfNearestTerm]->c();
					double d = terms[indexOfNearestTerm]->d();
					
					terms.remove(indexOfNearestTerm);

					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(a);
					newTerm->setB(b);
					newTerm->setC(c);
					newTerm->setD(d);
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else if ( (float)value>=terms[indexOfNearestTerm]->b() && (float)value<(terms[indexOfNearestTerm]->b()+terms[indexOfNearestTerm]->c())/2  )
				{
					double a = terms[indexOfNearestTerm]->a();

					terms[indexOfNearestTerm]->setA(value);
					terms[indexOfNearestTerm]->setB(terms[indexOfNearestTerm]->c());
			
					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(a);
					newTerm->setB(value);
					newTerm->setC(value);
					newTerm->setD(terms[indexOfNearestTerm]->b());
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else
				{
					terms[indexOfNearestTerm]->setA(value);
					terms[indexOfNearestTerm-1]->setD(value);
			
					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(terms[indexOfNearestTerm-1]->c());
					newTerm->setB(value);
					newTerm->setC(value);
					newTerm->setD(terms[indexOfNearestTerm]->b());
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
			}
			else // nearest term is the first term
			{
				if ((float)value==terms[indexOfNearestTerm]->a() && (float)value==terms[indexOfNearestTerm]->b()  && (float)value==terms[indexOfNearestTerm]->c())
				{
					double a = terms[indexOfNearestTerm]->a();
					double b = terms[indexOfNearestTerm]->b();
					double c = terms[indexOfNearestTerm]->c();
					double d = terms[indexOfNearestTerm]->d();
					
					terms.remove(indexOfNearestTerm);

					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(a);
					newTerm->setB(b);
					newTerm->setC(c);
					newTerm->setD(d);
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else if ((float)value==terms[indexOfNearestTerm]->b())
				{
					terms[indexOfNearestTerm]->setA(value);
					terms[indexOfNearestTerm]->setB(terms[indexOfNearestTerm]->c());

					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(min);
					newTerm->setB(value);
					newTerm->setC(value);
					newTerm->setD(terms[indexOfNearestTerm]->b());
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else if (value>=terms[indexOfNearestTerm]->a())
				{
					terms[indexOfNearestTerm]->setA(value);

					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(min);
					newTerm->setB(min);
					newTerm->setC(value);
					newTerm->setD(terms[indexOfNearestTerm]->b());
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else
				{
					if (value<min)
						min=value;

					terms[indexOfNearestTerm]->setA(value);

					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(min);
					newTerm->setB(min);
					newTerm->setC(value);
					newTerm->setD(terms[indexOfNearestTerm]->b());
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
			}
		}
		else if (value>terms[indexOfNearestTerm]->b() && value<= terms[indexOfNearestTerm]->c())
		{
			if (indexOfNearestTerm==terms.size()-1 && !terms[indexOfNearestTerm]->membership(min))
			{
				terms[indexOfNearestTerm]->setD(value);
				terms[indexOfNearestTerm]->setC(terms[indexOfNearestTerm]->b());

				if (value>max)
					max=value;

				TrapezTerm* newTerm = new TrapezTerm();
					
				newTerm->setA(terms[indexOfNearestTerm]->c());
				newTerm->setB(value);
				newTerm->setC(max);
				newTerm->setD(max);
				newTerm->setName(termName);

				terms.add(newTerm);
				termAdded = newTerm;
			}
			else if (indexOfNearestTerm==0)
			{
				if ( (float)value == terms[indexOfNearestTerm]->c())
				{	
					double a=terms[indexOfNearestTerm]->a();
					double b=terms[indexOfNearestTerm]->b();
					double c=terms[indexOfNearestTerm]->c();
					double d=terms[indexOfNearestTerm]->d();
					
					terms[indexOfNearestTerm]->setC(terms[indexOfNearestTerm]->b());
					terms[indexOfNearestTerm]->setD(value);

					TrapezTerm* newTerm = new TrapezTerm();
					
					if (b!=c)
					{
						newTerm->setA(terms[indexOfNearestTerm]->c());
						newTerm->setB(value);
						newTerm->setC(value);
						newTerm->setD(d);
					}
					else
					{
						newTerm->setA(a);
						newTerm->setB(b);
						newTerm->setC(c);
						newTerm->setD(d);

						terms.remove(indexOfNearestTerm);
					}
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
				else
				{
					terms[indexOfNearestTerm]->setA(value);
					terms[indexOfNearestTerm]->setB(terms[indexOfNearestTerm]->c());

					if (value<min)
						min = value;

					TrapezTerm* newTerm = new TrapezTerm();
					
					newTerm->setA(min);
					newTerm->setB(min);
					newTerm->setC(value);
					newTerm->setD(terms[indexOfNearestTerm]->b());
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
			}
			else if(value>(terms[indexOfNearestTerm]->b()+terms[indexOfNearestTerm]->c())/2 && value<=terms[indexOfNearestTerm]->c())
			{
				double b=terms[indexOfNearestTerm]->b();
				double d=terms[indexOfNearestTerm]->d();

				terms[indexOfNearestTerm]->setC(b);
				terms[indexOfNearestTerm]->setD(value);

				TrapezTerm* newTerm = new TrapezTerm();
					
				newTerm->setA(b);
				newTerm->setB(value);
				newTerm->setC(value);
				newTerm->setD(d);

				newTerm->setName(termName);

				terms.add(newTerm);
				termAdded = newTerm;
			}
			else
			{
				terms[indexOfNearestTerm]->setA(value);
				terms[indexOfNearestTerm]->setB(terms[indexOfNearestTerm]->c());
				terms[indexOfNearestTerm-1]->setD(value);
			
				TrapezTerm* newTerm = new TrapezTerm();
					
				newTerm->setA(terms[indexOfNearestTerm-1]->c());
				newTerm->setB(value);
				newTerm->setC(value);
				newTerm->setD(terms[indexOfNearestTerm]->b());
				newTerm->setName(termName);

				terms.add(newTerm);
				termAdded = newTerm;
			}
		}
		else if ((value>terms[indexOfNearestTerm]->c() && value<= terms[indexOfNearestTerm]->d()) || value>max)
		{
			terms[indexOfNearestTerm]->setD(value);

			if (terms.size()>indexOfNearestTerm+1)
			{
				terms[indexOfNearestTerm+1]->setA(value);
			
				TrapezTerm* newTerm = new TrapezTerm();

				newTerm->setA(terms[indexOfNearestTerm]->c());
				newTerm->setB(value);
				newTerm->setC(value);
				newTerm->setD(terms[indexOfNearestTerm+1]->b());
				newTerm->setName(termName);

				terms.add(newTerm);
				termAdded = newTerm;
			}
			else
			{
			//	if (value>(min+max)/2)
				{
					if (value>max)
						max=value;

					TrapezTerm* newTerm = new TrapezTerm();

					newTerm->setA(terms[indexOfNearestTerm]->c());
					newTerm->setB(value);
					newTerm->setC(max);
					newTerm->setD(max);
					newTerm->setName(termName);

					terms.add(newTerm);
					termAdded = newTerm;
				}
			/*	else
				{
					fl::TrapezoidalTerm* newTerm = new fl::TrapezoidalTerm();

					newTerm->setA(terms[indexOfNearestTerm]->c());
					newTerm->setB(value);
					newTerm->setC(value);
					newTerm->setD(max);
					newTerm->setName(std::string(termName.toUTF8()));

					terms.add(newTerm);
				} */
			}
		}

		sortTerms();

		if (termAdded)
		{
			int termIndex = -1;
			for (int i=0; i<terms.size(); i++)
				if (terms[i] == termAdded)
					termIndex = i;

			if (termIndex!=-1)
			{
				RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
				rpc->ruleGenerator.updateRulesBecauseOfNewTerm(this, termIndex);
			}
		}
	}
}

int TermManager::getIndex(double value)
{
	int index=-1;
	double maxMembership=-1;

	if (terms.size())
	{
		if (value<min)
		{
			index=0;
		}
		else if (value>max)
		{
			index=terms.size()-1;
		}
		else
			for (int i=0; i<terms.size(); i++)
			{
				if (terms[i]->membership(value)>=maxMembership)
				{
					maxMembership = terms[i]->membership(value);
					index = i;
				}
			}
	}

	return index;
}

void TermManager::removeTerm(int index)
{
	if (terms.size() == 1)
	{
		terms.remove(index);
	}
	else if (terms.size() == 2)
	{
		if (index==0)
		{
			terms[1]->setA(min);
		}
		else
		{
			terms[0]->setD(max);
		}
		terms.remove(index);
	}
	else
	{
		if (index==0)
		{
			if (terms.size()>1)
			{
				terms[index+1]->setA(min);
				terms[index+1]->setB(min);
			}
		}
		else if (index==terms.size()-1)
		{
			terms[index-1]->setC(max);
			terms[index-1]->setD(max);
		}
		else
		{
			terms[index-1]->setD(terms[index+1]->b());
			terms[index+1]->setA(terms[index-1]->c());
		}
		terms.remove(index);
	}
}

int TermManager::getIndex(String termName)
{
	bool found = false;

	int i=0;
	while (!found && i<terms.size())
	{
		if (termName.equalsIgnoreCase(String(terms[i]->name())))
		{
			found = true;
		}
		else
		{
			i++;
		}
	}

	if (found)
		return i;
	else
		return -1;
}

double TermManager::getMin()
{
	return min;
}

double TermManager::getMax()
{
	return max;
}

double TermManager::getMidPointOfTrapezoidTable(int index)
{
	bool found = true;
	if (index>=terms.size() || index<0)
		found = false;

	assert(found);

	return (terms[index]->b()+terms[index]->c())/2;
}

double TermManager::getMidPointOfTrapezoidTable(String termName)
{
	bool found = false;

	int i=0;
	while (!found && i<terms.size())
	{
		if (termName.compare(terms[i]->name()) == 0)
		{
			found = true;
		}
		else
		{
			i++;
		}
	}

	assert(found);

	return (terms[i]->b()+terms[i]->c())/2;
}

void TermManager::sortTerms()
{
	int i, j;
	for (i = 0; i < terms.size(); i++) 
    {
		for (j = 0; j < terms.size()-1; j++) 
        {
			if (getMidPointOfTrapezoidTable(j) > getMidPointOfTrapezoidTable(j+1)) 
            {
				terms.swap(j, j+1);
				//TrapezTerm* tmp = terms[j];
				//terms.set(j, terms[j + 1]);
				//terms.set(j+1, tmp);
            }
        }
     }
}

void TermManager::moveBtoTheLeft(int termIndex)
{
	double range = max-min;
	double targetValue = terms[termIndex]->b()-0.01*range;

	if (termIndex>0 && targetValue>terms[termIndex-1]->c())
	{
		terms[termIndex]->setB(targetValue);
		terms[termIndex-1]->setD(targetValue);
	}
	else if (termIndex==0 && targetValue>=min)
	{
		terms[termIndex]->setB(targetValue);
	}
	else if (targetValue<min)
	{
		terms[termIndex]->setB(min);
	} 
}

void TermManager::moveBtoTheRight(int termIndex)
{
	double range = max-min;
	double targetValue = terms[termIndex]->b()+0.01*range;

	if (targetValue>terms[termIndex]->c())
		targetValue = terms[termIndex]->c();

	if (termIndex>0)
	{
		terms[termIndex]->setB(targetValue);
		terms[termIndex-1]->setD(targetValue);
	}
	else if (targetValue<=terms[termIndex]->c() && terms[termIndex]->b()!=min)
	{
		terms[termIndex]->setB(targetValue);
	}
	else if (targetValue<=terms[termIndex]->c() && terms[termIndex]->b()==min && terms[termIndex]->c()==max)
	{
		terms[termIndex]->setB(targetValue);
	}
	else if (targetValue>terms[termIndex]->c() && terms[termIndex]->b()!=min)
	{
		terms[termIndex]->setB(terms[termIndex]->c());
	}
}

void TermManager::moveCtoTheLeft(int termIndex)
{
	double range = max-min;
	double targetValue = terms[termIndex]->c()-0.01*range;

	if (targetValue<terms[termIndex]->b())
		targetValue = terms[termIndex]->b();

	if (terms.size()>termIndex+1)
	{
		terms[termIndex]->setC(targetValue);
		terms[termIndex+1]->setA(targetValue);
	}
	else if (terms[termIndex]->c()!=max)
	{
		terms[termIndex]->setC(targetValue);
	}
	else if (terms[termIndex]->c()==max && terms[termIndex]->b()==min)
	{
		terms[termIndex]->setC(targetValue);
	}
}

void TermManager::moveCtoTheRight(int termIndex)
{
	double range = max-min;
	double targetValue = terms[termIndex]->c()+0.01*range;

	if (terms.size()>termIndex+1 && targetValue<terms[termIndex+1]->b())
	{
		terms[termIndex]->setC(targetValue);
		terms[termIndex+1]->setA(targetValue);
	}
	else if (terms.size()<=termIndex+1 && targetValue<=max)
	{
		terms[termIndex]->setC(targetValue);
	}
	else if (targetValue>max)
	{
		terms[termIndex]->setC(max);
	}
}