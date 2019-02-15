# MISofG-4-1-3-inHAT-forAAMAS19-
An analysis with a c++ code to show a result mentioned in my AAMAS19 paper:
  <Cooperation via Codes in Restricted Hat Guessing Games>
#################

Recall that the definition of G(4,1,3) is as follows. (Introduced in our orignial paper.)
  It has 7*6*5*4=840 nodes, each of which indexed by a 4-tuple (a1,a2,a3,a4), where a1,a2,a3,a4 are distinct numbers in range [1,7].  There is an edge between two nodes (a1,a2,a3,a4) an (b1,b2,b3,b4) if and only if the hamming distance between these two vectors (defined as \sum_{i=1..4}[ai\neq bi], where [] denotes the Iverson bracket) equals 1. 

We want to show that the size of MIS (maximum independent set) of G is (strictly) less than 840/4=210.
(Note that nodes in {(a1,a2,a3,*)} are all connected. This implies that |MIS| <= 210.)

#################

We use indirect proof. Let us suppose that there we can find an independent set I of G, which has 210 nodes.

Assign x_{a1,a2,a3,a4} = 1 if node (a1,a2,a3,a4) belongs to I and let it be 0 otherwise.
We have 840 variables x_{1234} ... x_{7654}.

We have 840 inequalities(using the fact I is an indpendent set):
   \sum_i x_{abci} <=1.  (For any three distinct numbers a,b,c in [1,7])
   \sum_i x_{abic} <=1. (For any three distinct numbers a,b,c in [1,7])
   \sum_i x_{aibc} <=1. (For any three distinct numbers a,b,c in [1,7])
   \sum_i x_{iabc} <=1. (For any three distinct numbers a,b,c in [1,7])
_____________________________
Claim: All of the above inequalitlies must be equations indeed.

%Proof%: If we have one strcit inequality among them, by summing up all the 840 inequalities, we get
   4 * \sum_{abcd} x_{abcd} < 840,  and hence \sum_{abcd} x_{abcd}<210.
But we know \sum_{abcd} x_{abcd}=210 since I has 210 nodes.

Corollary: For any three distinct numbers (a,b,c) in [1,7],
  there must be a unique i, defined as F(a,b,c) such that node (a,b,c,i) is in I.
Thus, from the set I we obtain a function F[a,b,c] defined on 7*6*5 values.
_____________
For convenience, let f1(b,c), ..., f7(b,c) be short for F[1,b,c], ..., F[7,b,c] respectively.
We state some properties of the seven functions f1 to f7 in the following.

Consider f1 for example. Define f1(k,k)=k which was previously undefined.
We know that {f1(b,c) | b,c in [2,7]} must be a Latin square of order 6 (with six symbols 2..7 and diagonal as 2..7).

Consider f7 for another example. Similary, define f7(k,k)=k.
We know that {f7(b,c) | b,c in [1,6]} must be a Latin square of order 6 (with six symbols 1..6 and diagonal as 1..6).

We can use a search algorithm to generate all possible tables of f1 .. f7. (See our cpp file)
By running our algorithm, we find that for each i in [7], fi has 10752 possible values.
！！！！！！
Next, we need to select a table for each fi (i = 1.. 7).
The time complexicty would be huge if we do it direct -- which is 10752^7.
However, an additional property (f1,..,f7) as follows can be explored here to speed up the running time.

%Additional Property%: the seven sets \{(b,c,f1(b,c)\}, \{(b,c,f2(b,c)\}, ..., \{(b,c),f7(b,c))\} must be disjoint. 
(More precisely, they together form a uniform partition of the set {(b,c,a)} of size 7*6*5=210.)

Our final algorithm runs in about half an hour to determine that there is no combination of (f1..f7) such that the above property holds. (We use Depth-First-Search. First, we try a value for f1. Then, try a value for f2 so that \{(b,c,f1(b,c)\}, \{(b,c,f2(b,c)\} are disjoint. Then, a value for f3 so that  \{(b,c,f1(b,c)\}, \{(b,c,f2(b,c)\},  \{(b,c,f3(b,c)\},  are disjoint, etc.)

！！！！！！
Note 1. We have checked that the propability for \{(b,c,fi(b,c)\}, \{(b,c,fj(b,c)\} to be disjoint is approximately 3% for any (i,j). That is why our algorithm runs in a time far smaller than 10752^7.

Note 2. If we don't use the above analysis, but directly use the Binary Linear programming algorithm for computing the MIS in some mathematic softwares (eg. sage or matlab), it is much more slower. A graph with 840 nodes is too large. 