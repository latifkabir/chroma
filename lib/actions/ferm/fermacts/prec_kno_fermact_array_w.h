// -*- C++ -*-
// $Id: prec_kno_fermact_array_w.h,v 2.2 2006-03-21 04:42:49 edwards Exp $
/*! \file
 *  \brief preconditioned KNO domain-wall fermion action
 */

#ifndef __prec_kno_fermact_array_w_h__
#define __prec_kno_fermact_array_w_h__

#include "fermact.h"
#include "actions/ferm/fermacts/prec_dwf_fermact_base_array_w.h"


namespace Chroma
{
  //! Name and registration
  namespace EvenOddPrecKNOFermActArrayEnv
  {
    extern const std::string name;
    extern const bool registered;
  }
  

  //! Params for NEFF
  struct EvenOddPrecKNOFermActArrayParams
  {
    EvenOddPrecKNOFermActArrayParams() {}
    EvenOddPrecKNOFermActArrayParams(XMLReader& in, const std::string& path);
    
    Real OverMass;
    Real Mass;
    Real a5 ;
    multi1d<Real> coefs;
    int  N5;
  };


  // Reader/writers
  void read(XMLReader& xml, const string& path, EvenOddPrecKNOFermActArrayParams& param);
  void write(XMLWriter& xml, const string& path, const EvenOddPrecKNOFermActArrayParams& param);


  //! EvenOddPreconditioned NEF fermion action
  /*! \ingroup fermacts
   *
   * EvenOddPrecondition NEF fermion action. The conventions used here
   * are specified in Phys.Rev.D63:094505,2001 (hep-lat/0005002).
   * See also Brower et.al. LATTICE04
   */
  class EvenOddPrecKNOFermActArray : public EvenOddPrecDWFermActBaseArray< LatticeFermion, multi1d<LatticeColorMatrix> >
  {
  public:
    //! General FermBC
    EvenOddPrecKNOFermActArray(Handle< FermBC< multi1d<LatticeFermion> > > fbc_, 
				   const Real& OverMass_, 
				   const Real& Mass_, 
			           const Real& a5_, 
				   const multi1d<Real>& c_,
				   int N5_) : 
      fbc(fbc_), OverMass(OverMass_), Mass(Mass_), a5(a5_), coefs(c_), N5(N5_) {init();}

    //! General FermBC
    EvenOddPrecKNOFermActArray(Handle< FermBC< multi1d<LatticeFermion> > > fbc_, 
			      const EvenOddPrecKNOFermActArrayParams& param) :
      fbc(fbc_), OverMass(param.OverMass), Mass(param.Mass), a5(param.a5), coefs(param.coefs), N5(param.N5) {init();}

    //! Copy constructor
    EvenOddPrecKNOFermActArray(const EvenOddPrecKNOFermActArray& a) : 
      fbc(a.fbc), OverMass(a.OverMass), Mass(a.Mass), a5(a.a5), coefs(a.coefs), N5(a.N5) {}

    //! Assignment
    EvenOddPrecKNOFermActArray& operator=(const EvenOddPrecKNOFermActArray& a)
      {
	fbc=a.fbc; 
	OverMass=a.OverMass; 
	Mass=a.Mass; 
	a5 = a.a5 ;
	coefs=a.coefs;
	N5=a.N5; 

	return *this;
      }

    //! Return the fermion BC object for this action
    const FermBC< multi1d<LatticeFermion> >& getFermBC() const {return *fbc;}

    //! Length of DW flavor index/space
    int size() const {return N5;}

    //! Return the quark mass
    Real getQuarkMass() const {return Mass;}

    //! Produce an unpreconditioned linear operator for this action with arbitrary quark mass
    const UnprecDWLikeLinOpBaseArray< LatticeFermion, multi1d<LatticeColorMatrix> >* unprecLinOp(Handle<const ConnectState> state, 
											     const Real& m_q) const;

    //! Produce an even-odd preconditioned linear operator for this action with arbitrary quark mass
    const EvenOddPrecDWLikeLinOpBaseArray< LatticeFermion, multi1d<LatticeColorMatrix> >* precLinOp(Handle<const ConnectState> state, 
												const Real& m_q) const;

    //! Destructor is automatic
    ~EvenOddPrecKNOFermActArray() {}

    //! Given a complete propagator as a source, this does all the inversions needed
    /*!
     * This routine is actually generic to Domain Wall fermions (Array) fermions
     *
     * \param q_sol    quark propagator ( Write )
     * \param q_src    source ( Read )
     * \param xml_out  diagnostic output ( Modify )
     * \param state    gauge connection state ( Read )
     * \param t_src    time slice of source ( Read )
     * \param j_decay  direction of decay ( Read )
     * \param invParam inverter parameters ( Read )
     * \param ncg_had  number of CG iterations ( Write )
     */
    void quarkProp(LatticePropagator& q_sol,
		   XMLWriter& xml_out,
		   const LatticePropagator& q_src,
		   int t_src, int j_decay,
		   Handle<const ConnectState> state,
		   const InvertParam_t& invParam,
		   QuarkSpinType quarkSpinType,
		   bool obsvP,
		   int& ncg_had);

  private:
    void init();

    void initCoeffs(multi1d<Real>& b5_arr, multi1d<Real>& c5_arr) const ;

  private:
    Handle< FermBC< multi1d<LatticeFermion> > >  fbc;
    Real OverMass;
    Real Mass;
    Real a5 ;
    multi1d<Real> coefs;
    int  N5;
  };

}

#endif
