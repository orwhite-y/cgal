// TODO: Add licence
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Arno Eigenwillig <arno@mpi-inf.mpg.de>
//                 Michael Seel <seel@mpi-inf.mpg.de>
//                 Michael Hemmer <hemmer@informatik.uni-mainz.de> 
//
// ============================================================================
#ifndef CGAL_POLYNOMIAL_TRAITS_D_H
#define CGAL_POLYNOMIAL_TRAITS_D_H

#include <CGAL/basic.h>
#include <CGAL/Polynomial/polynomial_utils.h>

CGAL_BEGIN_NAMESPACE

// The Polynomial_traits_d_base template
namespace CGALi {

template< class Innermost_coefficient_ >
class Polynomial_traits_d_base {
    typedef Innermost_coefficient_ ICoeff;
  public:
    static const int d = 0;
    
    typedef ICoeff Polynomial_d;
    typedef ICoeff Coefficient;
    typedef ICoeff Innermost_coefficient;
    
    struct Degree 
        : public Unary_function< ICoeff , int > {
        int operator()(const ICoeff& c) const { return 0; }
    };
    struct Total_degree 
        : public Unary_function< ICoeff , int > {
        int operator()(const ICoeff& c) const { return 0; }
    };
    
    typedef Null_functor  Construct_polynomial;
    typedef Null_functor  Degree;
    typedef Null_functor  Total_degree;
    typedef Null_functor  Leading_coefficient;
    typedef Null_functor  Univariate_content;
    typedef Null_functor  Multivariate_content;
    typedef Null_functor  Shift;
    typedef Null_functor  Negate;
    typedef Null_functor  Invert;
    typedef Null_functor  Translate;
    typedef Null_functor  Translate_homogeneous;
    typedef Null_functor  Scale_homogeneous;
    typedef Null_functor  Differentiate;
    
    struct Make_square_free 
        : public Unary_function< ICoeff, ICoeff>{
        ICoeff operator()( const ICoeff& x ) const {
            if (CGAL::is_zero(x)) return x ;
            else  return ICoeff(1);
        }
    };
        
    typedef Null_functor  Square_free_factorization;
    typedef Null_functor  Pseudo_division;
    typedef Null_functor  Pseudo_division_remainder;
    typedef Null_functor  Pseudo_division_quotient;

    struct Gcd_up_to_constant_factor 
        : public Binary_function< ICoeff, ICoeff, ICoeff >{
        ICoeff operator()(const ICoeff& x, const ICoeff& y) const {
            if (CGAL::is_zero(x) && CGAL::is_zero(y)) 
                return ICoeff(0);
            else
                return ICoeff(1);
        }
    };
    typedef Null_functor  Integral_division_up_to_constant_factor;
    struct Univariate_content_up_to_constant_factor
        : public Unary_function< ICoeff, ICoeff >{
        ICoeff operator()(const ICoeff& ) const {
            return ICoeff(1);
        }
    };

    typedef Null_functor  Square_free_factorization_up_to_constant_factor;
    typedef Null_functor  Evaluate;
    typedef Null_functor  Evaluate_homogeneous;
    typedef Null_functor  Resultant;
    typedef Null_functor  Canonicalize;
    
    struct Innermost_leading_coefficient
        :public Unary_function <ICoeff, ICoeff>{
        ICoeff operator()(const ICoeff& x){return x;}
    };
    struct Degree_vector{
        typedef std::vector<int>        result_type;
        typedef Coefficient             argument_type;
        
        // returns the exponent vector of inner_most_lcoeff. 
        result_type operator()(const Coefficient& constant){
            return std::vector<int>();
        }
    };
};

} // namespace CGALi

template < class T > class Polynomial_traits_d
    :public CGALi::Polynomial_traits_d_base<T> {};

template < class Coefficient_ > 
class Polynomial_traits_d< Polynomial<Coefficient_> >
    :public CGALi::Polynomial_traits_d_base< Polynomial<Coefficient_> > {
    
    typedef Polynomial_traits_d< Coefficient_ > PTC;
    typedef Polynomial_traits_d< Polynomial< Coefficient_ > > PT;
  
public:
    typedef Polynomial<Coefficient_>                  Polynomial_d;
    typedef Coefficient_                              Coefficient;
    typedef typename PTC::Innermost_coefficient       Innermost_coefficient;
    static const int d                              = PTC::d+1;

private:
    typedef std::pair< Exponent_vector, Innermost_coefficient > 
    Exponents_coeff_pair;
    typedef std::vector< Exponents_coeff_pair > Monom_rep; 
public:

    struct Construct_polynomial {
        
        typedef Polynomial_d  result_type;
        
        Polynomial_d operator()()  const {
            return Polynomial_d(0);
        }
        
        template <class T>
        Polynomial_d operator()( T a ) const {
            return Polynomial_d(a);
        }
        
        //! construct the constant polynomial a0
        Polynomial_d operator() (const Coefficient& a0) const
        {return Polynomial_d(a0);}
        
        //! construct the polynomial a0 + a1*x
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1) const
        {return Polynomial_d(a0,a1);}
        
        //! construct the polynomial a0 + a1*x + a2*x^2
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2) const
        {return Polynomial_d(a0,a1,a2);}
        
        //! construct the polynomial a0 + a1*x + ... + a3*x^3
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2, const Coefficient& a3) const
        {return Polynomial_d(a0,a1,a2,a3);}
        
        //! construct the polynomial a0 + a1*x + ... + a4*x^4
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2, const Coefficient& a3,
                const Coefficient& a4) const
        {return Polynomial_d(a0,a1,a2,a3,a4);}
        
        //! construct the polynomial a0 + a1*x + ... + a5*x^5
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2, const Coefficient& a3,
                const Coefficient& a4, const Coefficient& a5) const
        {return Polynomial_d(a0,a1,a2,a3,a4,a5);}
        
        //! construct the polynomial a0 + a1*x + ... + a6*x^6
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2, const Coefficient& a3,
                const Coefficient& a4, const Coefficient& a5, 
                const Coefficient& a6) const
        {return Polynomial_d(a0,a1,a2,a3,a4,a5,a6);}
        
        //! construct the polynomial a0 + a1*x + ... + a7*x^7
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2, const Coefficient& a3,
                const Coefficient& a4, const Coefficient& a5, 
                const Coefficient& a6, const Coefficient& a7) const
        {return Polynomial_d(a0,a1,a2,a3,a4,a5,a6,a7);}
        
        //! construct the polynomial a0 + a1*x + ... + a8*x^8
        Polynomial_d operator() (
                const Coefficient& a0, const Coefficient& a1,
                const Coefficient& a2, const Coefficient& a3,
                const Coefficient& a4, const Coefficient& a5, 
                const Coefficient& a6, const Coefficient& a7,
                const Coefficient& a8) const 
        {return Polynomial_d(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
        
        template< class Input_iterator >
        inline
        Polynomial_d construct( 
                Input_iterator begin, 
                Input_iterator end , 
                Tag_true) const {
            return Polynomial_d(begin,end);
        }
        
        template< class Input_iterator >
        inline
        Polynomial_d construct( 
                Input_iterator begin, 
                Input_iterator end , 
                Tag_false) const {
            std::sort(begin,end); 
            return Create_polynomial_from_monom_rep< Coefficient >()
                ( begin, end ); 
        }
        

        template< class Input_iterator >
        Polynomial_d 
        operator()( Input_iterator begin, Input_iterator end ) const {
            if(begin == end ) return Polynomial_d(0);
            typedef typename Input_iterator::value_type value_type;
            typedef Boolean_tag<boost::is_same<value_type,Coefficient>::value> 
                Is_coeff;
            return construct(begin,end,Is_coeff());
        }
    
    private:

        template< class T >
        class Create_polynomial_from_monom_rep {
        public:
            template <class Monom_rep_iterator>
            Polynomial_d operator()( 
                    Monom_rep_iterator begin,
                    Monom_rep_iterator end) const {
                
                std::vector< Innermost_coefficient > coefficients;
                for(Monom_rep_iterator it = begin; it != end; it++){
                    while( it->first[0] > (int) coefficients.size() ){
                        coefficients.push_back(Innermost_coefficient(0));
                    }
                    coefficients.push_back(it->second);
                }
                return Polynomial_d(coefficients.begin(),coefficients.end());
            }
        };
        
        template< class T >
        class Create_polynomial_from_monom_rep< Polynomial < T > > {
        public:
            template <class Monom_rep_iterator>
            Polynomial_d operator()( 
                    Monom_rep_iterator begin,
                    Monom_rep_iterator end) const {
                //std::cout << " ------\n "  << std::endl;
                
                typedef Polynomial_traits_d<Coefficient> PT;
                typename PT::Construct_polynomial construct;
                
                BOOST_STATIC_ASSERT(PT::d != 0); // Coefficient is a Polynomial
                std::vector<Coefficient> coefficients;
                
                Monom_rep_iterator it = begin; 
                while(it != end){
                    int current_exp = it->first[PT::d];
                    //std::cout <<"current_exp: " <<  current_exp << std::endl;
                    // fill up with zeros until current exp is reached
                    while( (int) coefficients.size() < current_exp){
                        coefficients.push_back(Coefficient(0));
                        //std::cout <<" insert "<< std::endl;
                    }
                    // collect all coeffs for this exp
                    Monom_rep monoms; 
                    while(  it != end && it->first[PT::d] == current_exp ){
                        Exponent_vector ev = it->first;
                        ev.pop_back();
                        monoms.push_back( Exponents_coeff_pair(ev,it->second));
                        it++;
                    }                    
                    coefficients.push_back(
                                construct(monoms.begin(), monoms.end()));
                }
                //std::cout << " ------\n "  << std::endl;
                return Polynomial_d(coefficients.begin(),coefficients.end());
            }
        };
    };


    struct Get_monom_representation {      
        typedef std::pair< Exponent_vector, Innermost_coefficient >
        Exponents_coeff_pair;
        typedef std::vector< Exponents_coeff_pair > Monom_rep; 
        
        template <class OutputIterator>
        void operator()( const Polynomial_d& p, OutputIterator oit ) const {
            typedef Boolean_tag< d == 1 > Is_univariat;
            create_monom_representation( p, oit , Is_univariat());
        }
      
      private:
        
        template <class OutputIterator>
        void
        create_monom_representation 
        ( const Polynomial_d& p, OutputIterator oit, Tag_true ) const{
            for( int exponent = 0; exponent <= p.degree(); ++exponent ) {
                // std::cout << "p[exponent]: "<<p[exponent];
                if ( p[exponent] != Coefficient(0) ){
                    Exponent_vector exp_vec;
                    exp_vec.push_back( exponent );
                    *oit = Exponents_coeff_pair( exp_vec, p[exponent] ); 
                }
            } 
        } 
        template <class OutputIterator>
        void 
        create_monom_representation 
        ( const Polynomial_d& p, OutputIterator oit, Tag_false ) const { 
            for( int exponent = 0; exponent <= p.degree(); ++exponent ) {
                Monom_rep monom_rep;
                typedef Polynomial_traits_d< Coefficient > PT;
                typename PT::Get_monom_representation gmr;
                gmr( p[exponent], std::back_inserter( monom_rep ) );
                for( typename Monom_rep::iterator it = monom_rep.begin();
                     it != monom_rep.end(); ++it ) {
                    it->first.push_back( exponent );
                }
                copy( monom_rep.begin(), monom_rep.end(), oit );               
            }
        }
    };
private:
    typedef CGAL::Recursive_const_flattening< d-1, 
    typename CGAL::Polynomial<Coefficient>::const_iterator > 
    Coefficient_flattening;

public:

    typedef typename  Polynomial_d::iterator Coefficient_iterator;
    struct Coefficient_begin 
        : public Unary_function< Polynomial_d, Coefficient_iterator > {
        Coefficient_iterator 
        operator () (const Polynomial_d& p) { return p.begin(); }
    }; 
    struct Coefficient_end 
        : public Unary_function< Polynomial_d, Coefficient_iterator > {
        Coefficient_iterator 
        operator () (const Polynomial_d& p) { return p.end(); }
    };

public:
    typedef typename Coefficient_flattening::Recursive_flattening_iterator
    Innermost_coefficient_iterator;

    struct Innermost_coefficient_begin 
        : public Unary_function< Polynomial_d, Innermost_coefficient_iterator > {
        Innermost_coefficient_iterator
        operator () (const Polynomial_d& p) {
            return typename Coefficient_flattening::Flatten()(p.end(),p.begin());
        }
    };

    struct Innermost_coefficient_end 
      : public Unary_function< Polynomial_d, Innermost_coefficient_iterator > {
        Innermost_coefficient_iterator
        operator () (const Polynomial_d& p) {
            return typename Coefficient_flattening::Flatten()(p.end(),p.end());
        }
    };

    // Swap variable x_i with x_j
    struct Swap {
        typedef Polynomial_d        result_type;  
        typedef Polynomial_d        first_argument_type;
        typedef int                 second_argument_type;
        typedef int                 third_argument_type;
        typedef Arity_tag< 3 >         Arity;
        
        Polynomial_d operator()(const Polynomial_d& p, int i, int j ) const {
            //std::cout << i <<" " << j << " : " ; 
            CGAL_precondition(0 <= i && i < d);
            CGAL_precondition(0 <= j && j < d);
            typedef std::pair< Exponent_vector, Innermost_coefficient >
                Exponents_coeff_pair;
            typedef std::vector< Exponents_coeff_pair > Monom_rep; 
            Get_monom_representation gmr;
            Construct_polynomial construct;
            Monom_rep mon_rep;
            gmr( p, std::back_inserter( mon_rep ) );
            for( typename Monom_rep::iterator it = mon_rep.begin(); 
                 it != mon_rep.end();
                 ++it ) {
                std::swap(it->first[i],it->first[j]);
                // it->first.swap( i, j );
            }
            std::sort( mon_rep.begin(), mon_rep.end() );
            return construct( mon_rep.begin(), mon_rep.end() );
        }
    };

    // move variable x_i to position of x_j
    // order of other variables remains 
    // default j = d makes x_i the othermost variable
 struct Move {
        typedef Polynomial_d        result_type;  
        typedef Polynomial_d        first_argument_type;
        typedef int                 second_argument_type;
        typedef int                 third_argument_type;
        typedef Arity_tag< 3 >         Arity;
        
        Polynomial_d operator()(const Polynomial_d& p, int i, int j = (d-1) ) const {
            //std::cout << x <<" " << y << " : " ; 
            CGAL_precondition(0 <= i && i < d);
            CGAL_precondition(0 <= j && j < d);
            typedef std::pair< Exponent_vector, Innermost_coefficient >
                Exponents_coeff_pair;
            typedef std::vector< Exponents_coeff_pair > Monom_rep; 
            Get_monom_representation gmr;
            Construct_polynomial construct;
            Monom_rep mon_rep;
            gmr( p, std::back_inserter( mon_rep ) );
            for( typename Monom_rep::iterator it = mon_rep.begin(); 
                 it != mon_rep.end();
                 ++it ) {
                // this is as good as std::rotate since it uses swap also
                if (i < j) 
                    for( int k = i; k < j; k++ )
                        std::swap(it->first[k],it->first[k+1]);
                else
                    for( int k = i; k > j; k-- )
                        std::swap(it->first[k],it->first[k-1]);
                
            }
            std::sort( mon_rep.begin(), mon_rep.end() );
            return construct( mon_rep.begin(), mon_rep.end() );
        }
    };
    
    struct Degree : public Unary_function< Polynomial_d , int  >{
        int operator()(const Polynomial_d& p, int i = (d-1)) const {      
            if (i == (d-1)) return p.degree();                           
            else return Swap()(p,i,d-1).degree();
        }     
    };

    //       Total_degree;
    struct Total_degree : public Unary_function< Polynomial_d , int >{
        int operator()(const Polynomial_d& p) const {
            typedef Polynomial_traits_d<Coefficient> COEFF_POLY_TRAITS;
            typename COEFF_POLY_TRAITS::Total_degree total_degree;
            Degree degree;
            CGAL_precondition( degree(p) >= 0);

            int result = 0;
            for(int i = 0; i <= degree(p) ; i++){
                if( ! CGAL::is_zero( p[i]) )
                    result = std::max(result , total_degree(p[i]) + i );
            } 
            return result;
        }
    };
//       Leading_coefficient;
    struct Leading_coefficient 
        : public Unary_function< Polynomial_d , Coefficient>{
        Coefficient operator()(const Polynomial_d& p) const {
            return p.lcoeff();
        }
        Coefficient operator()(Polynomial_d p, int i) const {
            return Swap()(p,i,PT::d-1).lcoeff();
        }
    };
    struct Innermost_leading_coefficient 
        : public Unary_function< Polynomial_d , Innermost_coefficient>{
        Innermost_coefficient 
        operator()(const Polynomial_d& p) const {
            typename PTC::Innermost_leading_coefficient ilcoeff;
            typename PT::Leading_coefficient lcoeff;
            return ilcoeff(lcoeff(p));
        }
    };
    // returns the Exponten_vector of the innermost leading coefficient 
    // TODO use Exponent vector 
    // TODO document 
    struct Degree_vector{
        typedef std::vector<int>        result_type;
        typedef Polynomial_d              argument_type;
        
        // returns the exponent vector of inner_most_lcoeff. 
        result_type operator()(const Polynomial_d& polynomial){
            
            typename PTC::Degree_vector degree_vector;
            
            std::vector<int> result = degree_vector(polynomial.lcoeff());
            result.insert(result.begin(),polynomial.degree());
            return result;
        }
    };
    
//       Univariate_content;
    struct Univariate_content
        : public Unary_function< Polynomial_d , Coefficient>{
        Coefficient operator()(const Polynomial_d& p) const {
            return p.content();
        }
        Coefficient operator()(Polynomial_d p, int i) const {
            return Swap()(p,i,PT::d-1).content();
        }
    };
//       Multivariate_content;
    struct Multivariate_content
        : public Unary_function< Polynomial_d , Innermost_coefficient >{
        Innermost_coefficient 
        operator()(const Polynomial_d& p) const {
            typedef Innermost_coefficient_iterator IT;
            Innermost_coefficient content(0);
            for (IT it = Innermost_coefficient_begin()(p);
                 it != Innermost_coefficient_end()(p);
                 it++){
                content = CGAL::gcd(content, *it);
                if(CGAL::is_one(content)) break;
            }
            return content;
        }
    };
//       Shift;
    struct Shift
        : public Unary_function< Polynomial_d, Polynomial_d >{
        Polynomial_d 
        operator()(const Polynomial_d& p, int e, int i = PT::d) const {
            Construct_polynomial construct; 
            Get_monom_representation gmr; 
            Monom_rep monom_rep;
            gmr(p,std::back_inserter(monom_rep));
            for(typename Monom_rep::iterator it = monom_rep.begin(); 
                it != monom_rep.end();
                it++){
                it->first[i-1]+=e;
            }
            return construct(monom_rep.begin(), monom_rep.end());
        }
    };
//       Negate;
    struct Negate
        : public Unary_function< Polynomial_d, Polynomial_d >{
        
        Polynomial_d operator()(const Polynomial_d& p, int i = (d-1)) const {
            Construct_polynomial construct; 
            Get_monom_representation gmr; 
            Monom_rep monom_rep;
            gmr(p,std::back_inserter(monom_rep));
            for(typename Monom_rep::iterator it = monom_rep.begin(); 
                it != monom_rep.end();
                it++){
                if (it->first[i] % 2 != 0) 
                    it->second = - it->second; 
            }
            return construct(monom_rep.begin(), monom_rep.end());
        }
    };
//       Invert;
    struct Invert
        : public Unary_function< Polynomial_d , Polynomial_d >{
        Polynomial_d operator()(Polynomial_d p, int i = (PT::d-1)) const {
            if (i == (d-1)){
                p.reversal(); 
            }else{
                p =  Swap()(p,i,PT::d-1);
                p.reversal();
                p = Swap()(p,i,PT::d-1);   
            }
            return p ;
        }
    };
//       Translate;
    struct Translate
        : public Binary_function< Polynomial_d , Polynomial_d, 
                                  Innermost_coefficient >{
        Polynomial_d
        operator()(
                Polynomial_d p, 
                const Innermost_coefficient& c, 
                int i = (d-1)) 
            const {
            if (i == (d-1) ){
                p.translate(Coefficient(c)); 
            }else{
                Swap swap;
                p = swap(p,i,d-1);
                p.translate(Coefficient(c));
                p = swap(p,i,d-1); 
            }
            return p;
        }
    };

//       Translate_homogeneous;
    struct Translate_homogeneous{
        typedef Polynomial_d result_type;
        typedef Polynomial_d first_argument_type;
        typedef Innermost_coefficient second_argument_type;
        typedef Innermost_coefficient third_argument_type;
        
        Polynomial_d
        operator()(Polynomial_d p, 
                const Innermost_coefficient& a, 
                const Innermost_coefficient& b,
                int i = (d-1) ) const {
            if (i == (d-1) ){
                p.translate(Coefficient(a), Coefficient(b) );  
            }else{
                Swap swap;
                p = swap(p,i,d-1);
                p.translate(Coefficient(a), Coefficient(b));
                p = swap(p,i,d-1);
            }
            return p;
         }
    };

//       Scale_homogeneous;
    struct Scale_homogeneous{
        typedef Polynomial_d result_type;
        typedef Polynomial_d first_argument_type;
        typedef Innermost_coefficient second_argument_type;
        typedef Innermost_coefficient third_argument_type;
        
        Polynomial_d
        operator()(
                Polynomial_d p, 
                const Innermost_coefficient& a, 
                const Innermost_coefficient& b,
                int i = (d-1) ) const {
            CGAL_precondition( ! CGAL::is_zero(b) );
            
            if (i == (d-1) ) p = Swap()(p,i,d-1);
          
            if(CGAL::is_one(b)) 
                p.scale_up(Coefficient(a));
            else 
                if(CGAL::is_one(a)) 
                    p.scale_down(Coefficient(b));
                else 
                    p.scale(Coefficient(a), Coefficient(b) );  
          
            if (i == (d-1) ) p = Swap()(p,i,d-1);
          
            return p;
         }
    };

//       Differentiate;
     struct Differentiate 
         : public Unary_function<Polynomial_d, Polynomial_d>{
        Polynomial_d
        operator()(Polynomial_d p, int i = (d-1)) const {
            if (i == (d-1) ){
                p.diff();
            }else{
                Swap swap;
                p = swap(p,i,d-1);
                p.diff();
                p = swap(p,i,d-1);
            }
            return p;
         }
    };
//       Make_square_free;
    struct Make_square_free 
        : public Unary_function< Polynomial_d, Polynomial_d >{
        Polynomial_d
        operator()(const Polynomial_d& p) const {
            if (CGAL::is_zero(p)) return p;
            Univariate_content_up_to_constant_factor ucontent_utcf;
            Integral_division_up_to_constant_factor  idiv_utcf;
            Differentiate diff;
            typename PTC::Make_square_free msf;
            
            Coefficient content = ucontent_utcf(p);
            Polynomial_d result = Polynomial_d(msf(content));
            
            Polynomial_d regular_part = idiv_utcf(p,Polynomial_d(content));
            Polynomial_d g = gcd_utcf(regular_part,diff(regular_part));
            
            result *= idiv_utcf(regular_part,g);
            return Canonicalize()(result);
           
#if 0
           
            Square_free_factorization sqff_utcf;
            std::vector<Polynomial_d> facs;
            std::vector<int> mults;
            sqff_utcf(p,std::back_inserter(facs), std::back_inserter(mults));
            for(typename std::vector<Polynomial_d>::iterator it = facs.begin();
                it != facs.end();
                it++){
                result *= *it;
            }   
            return result;
#endif
         
        }
    };

// Square_free_factorization;
    struct Square_free_factorization{
        typedef int result_type;
        
    private:
        typedef Coefficient Coeff;
        typedef Innermost_coefficient ICoeff;

        // rsqff computes the sqff recursively for Coeff  
        // end of recursion: ICoeff
        template < class OutputIterator1, class OutputIterator2 >
        int rsqff  (ICoeff c, 
                OutputIterator1 factors, 
                OutputIterator2 mults) const{
            return 0;
        }        
        template < class OutputIterator1, class OutputIterator2 >
        int rsqff (
                typename First_if_different<Coeff,ICoeff>::Type c,
                OutputIterator1 fit, 
                OutputIterator2 mit) const {
            typename PTC::Square_free_factorization sqff;
            std::vector<Coefficient> factors;
            int n = sqff(c, std::back_inserter(factors), mit);
            for(int i = 0; i < (int)factors.size(); i++){
                *fit++=Polynomial_d(factors[i]);
            }
            return n; 
        }
    public:
        template < class OutputIterator1, class OutputIterator2 >
        int operator()(
                const Polynomial_d& p, 
                OutputIterator1 fit, 
                OutputIterator2 mit) const {
            Coefficient c; 
            int n = square_free_factorization(p,fit,mit,c);
            if (Total_degree()(c) > 0) 
                return rsqff(c,fit,mit)+n;
            else 
                return n;
        }  
    };
    
//       Pseudo_division;
    struct Pseudo_division {
        typedef Polynomial_d        result_type;  
        void
        operator()(
                const Polynomial_d& f, const Polynomial_d& g,
                Polynomial_d& q, Polynomial_d& r, Coefficient& D) const {
            Polynomial_d::pseudo_division(f,g,q,r,D);
        }
    };
//       Pseudo_division_remainder;
    struct Pseudo_division_remainder
        :public Binary_function<Polynomial_d, Polynomial_d, Polynomial_d> {
        
        Polynomial_d
        operator()(const Polynomial_d& f, const Polynomial_d& g) const {
            Polynomial_d q,r;
            Coefficient D;
            Polynomial_d::pseudo_division(f,g,q,r,D);
            return r;
        }
    };
//       Pseudo_division_quotient;
    struct Pseudo_division_quotient
        :public Binary_function<Polynomial_d, Polynomial_d, Polynomial_d> {
        
        Polynomial_d
        operator()(const Polynomial_d& f, const Polynomial_d& g) const {
            Polynomial_d q,r;
            Coefficient D;
            Polynomial_d::pseudo_division(f,g,q,r,D);
            return q;
        }
    };
//       Gcd_up_to_constant_factor;
    struct Gcd_up_to_constant_factor
        :public Binary_function<Polynomial_d, Polynomial_d, Polynomial_d> {
        Polynomial_d
        operator()(const Polynomial_d& p, const Polynomial_d& q) const {
            if (CGAL::is_zero(p) && CGAL::is_zero(q)) 
                return Polynomial_d(0);
            return gcd_utcf(p,q);
        }
    };
    
//       Integral_division_up_to_constant_factor;
    struct Integral_division_up_to_constant_factor
        :public Binary_function<Polynomial_d, Polynomial_d, Polynomial_d> {
        Polynomial_d
        operator()(const Polynomial_d& p, const Polynomial_d& q) const {
            typedef Innermost_coefficient IC;

            typename PT::Construct_polynomial construct;
            typename PT::Innermost_leading_coefficient ilcoeff;
            typename PT::Innermost_coefficient_begin begin;
            typename PT::Innermost_coefficient_end end;
            typedef Algebraic_extension_traits<Innermost_coefficient> AET;
            typename AET::Denominator_for_algebraic_integers dfai;
            typename AET::Normalization_factor nfac;

            
            IC ilcoeff_q = ilcoeff(q);
            // this factor is needed in case IC is an Algebraic extension
            IC dfai_q = dfai(begin(q), end(q));
            // make dfai_q a 'scalar'
            ilcoeff_q *= dfai_q * nfac(dfai_q);
            Polynomial_d result = (p * construct(ilcoeff_q)) / q;

            return Canonicalize()(result);
        }
    };
    
//     Univariate_content_up_to_constant_factor;
    struct Univariate_content_up_to_constant_factor
        :public Unary_function<Polynomial_d, Coefficient> {
        Coefficient
        operator()(const Polynomial_d& p) const {
            typename PTC::Gcd_up_to_constant_factor gcd_utcf;
            
            if(CGAL::is_zero(p)) return Coefficient(0);
            if(PT::d == 1) return Coefficient(1);

            Coefficient result(0);
            for(typename Polynomial_d::const_iterator it = p.begin();
                it != p.end();
                it++){
                result = gcd_utcf(*it,result);
            }
            return result;

        }
    };
//       Square_free_factorization_up_to_constant_factor;
    struct Square_free_factorization_up_to_constant_factor {
        typedef int result_type;
    private:
        typedef Coefficient Coeff;
        typedef Innermost_coefficient ICoeff;
        
        // rsqff_utcf computes the sqff recursively for Coeff  
        // end of recursion: ICoeff
        template < class OutputIterator1, class OutputIterator2 >
        int rsqff_utcf  (ICoeff c, 
                OutputIterator1 factors, 
                OutputIterator2 mults) const{
            return 0;
        }        
        template < class OutputIterator1, class OutputIterator2 >
        int rsqff_utcf (
                typename First_if_different<Coeff,ICoeff>::Type c,
                OutputIterator1 fit, 
                OutputIterator2 mit) const {
            typename PTC::Square_free_factorization sqff;
            std::vector<Coefficient> factors;
            int n = sqff(c, std::back_inserter(factors), mit);
            for(int i = 0; i < (int)factors.size(); i++){
                *fit++=Polynomial_d(factors[i]);
            }
            return n; 
        }
    public:
        template < class OutputIterator1, class OutputIterator2 >
        int operator()(
                Polynomial_d p, 
                OutputIterator1 fit, 
                OutputIterator2 mit) const {
            
            if (CGAL::is_zero(p)) return 0;

            Univariate_content_up_to_constant_factor ucontent_utcf;
            Integral_division_up_to_constant_factor idiv_utcf;
            Coefficient c = ucontent_utcf(p);
            p = idiv_utcf( p , Polynomial_d(c));
            int n = square_free_factorization_utcf(p,fit,mit);
            if (Total_degree()(c) > 0) 
                    return rsqff_utcf(c,fit,mit)+n;
                else 
                    return n;
        }
    };
    
//       Evaluate;
    struct Evaluate
        :public Binary_function<Polynomial_d,Innermost_coefficient,Coefficient>{
        Coefficient
        operator()(const Polynomial_d& p, Innermost_coefficient x, int i = (d-1)) 
            const {
            if(i == (d-1) )
                return p.evaluate(x);
            else{
                return Move()(p,i).evaluate(x);
            }
        }
    };
//       Evaluate_homogeneous;
    struct Evaluate_homogeneous{
        typedef Coefficient           result_type;  
        typedef Polynomial_d          first_argument_type;
        typedef Innermost_coefficient second_argument_type;
        typedef Innermost_coefficient third_argument_type;
        typedef Arity_tag< 3 >         Arity;
        
        Coefficient
        operator()(
                const Polynomial_d& p, 
                Innermost_coefficient a, 
                Innermost_coefficient b) const {
                 return p.evaluate_homogeneous(a,b);
        }  
        Coefficient
        operator()(
                const Polynomial_d& p, 
                Innermost_coefficient a, 
                Innermost_coefficient b,
                int hdegree ,
                int i = (PT::d-1) ) const {
            if (i == (d-1) )
                return p.evaluate_homogeneous(a,b,hdegree);
            else
                return Move()(p,i,PT::d-1).evaluate_homogeneous(a,b,hdegree);
        }         
    };
    
//       Resultant;
    struct Resultant
        : public Binary_function<Polynomial_d, Polynomial_d, Coefficient>{
        
        Coefficient
        operator()(
                const Polynomial_d& p, 
                const Polynomial_d& q,
                int i = (d-1) ) const {
            if(i == (d-1) )
                return prs_resultant(p,q);
            else
                return prs_resultant(Move()(p,i),Move()(q,i));
        }  
     };
    
//       Canonicalize;
    struct Canonicalize
        : public Unary_function<Polynomial_d, Polynomial_d>{
        Polynomial_d
        operator()( const Polynomial_d& p ) const {
            return CGAL::INTERN_POLYNOMIAL::canonicalize_polynomial(p);
        }  
     };
};

CGAL_END_NAMESPACE

#endif // CGAL_POLYNOMIAL_TRAITS_D_H
