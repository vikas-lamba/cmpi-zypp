
#include <iostream>

#include <cmpi/cmpimacs.h>
#include <cmpi/cmpidt.h>
#include <cmpi/CmpiResult.h>
#include <cmpi/CmpiBroker.h>
#include <cmpi/CmpiArray.h>
#include <cmpi/CmpiBooleanData.h>

#include <zypp/base/String.h>
#include <zypp/base/LogTools.h>

#include "SUSE_zypp.h"
#include "SUSE_Common.h"
#include "SUSE_HostedInstallationServiceProvider.h"

using namespace zypp;
using std::endl;

namespace cmpizypp
{
  namespace
  {
    const char * _ClassName     = "SUSE_HostedInstallationService";
    const char * _RefLeft       = "Antecedent";
    const char * _RefRight      = "Dependent";
    const char * _RefLeftClass  = "CIM_ComputerSystem";
    const char * _RefRightClass = "SUSE_SoftwareInstallationService";

  } // namespace

  SUSE_HostedInstallationServiceProviderClass::SUSE_HostedInstallationServiceProviderClass( const CmpiBroker & mbp, const CmpiContext & ctx )
  : CmpiBaseMI( mbp, ctx )
  , CmpiInstanceMI( mbp, ctx )
  , CmpiAssociationMI( mbp, ctx )
  {
  }

  CmpiStatus SUSE_HostedInstallationServiceProviderClass::enumInstanceNames( const CmpiContext& ctx, CmpiResult& rslt, const CmpiObjectPath & cop )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI EnumInstanceNames() called",_ClassName));

    CmpiObjectPath csop = get_this_computersystem(*broker, ctx, cop);
    bool ret = assoc_create_refs_1toN( *broker, ctx, rslt, csop,
                                       _ClassName,_RefLeft,_RefRight,
                                       _RefLeftClass,_RefRightClass,0,0);
    if(!ret)
    {
      CmpiStatus st( CMPI_RC_ERR_FAILED, "EnumInstanceNames failed." );
      return st;
    }

    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI EnumInstanceNames() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
  }

  CmpiStatus SUSE_HostedInstallationServiceProviderClass::enumInstances( const CmpiContext & ctx, CmpiResult & rslt, const CmpiObjectPath & cop, const char** properties )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI EnumInstances() called",_ClassName));

    CmpiObjectPath csop = get_this_computersystem(*broker, ctx, cop);
    bool ret = assoc_create_refs_1toN( *broker, ctx, rslt, csop,
                                       _ClassName,_RefLeft,_RefRight,
                                       _RefLeftClass,_RefRightClass,1,0);
    if(!ret)
    {
      CmpiStatus st( CMPI_RC_ERR_FAILED, "EnumInstances failed." );
      return st;
    }

    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI EnumInstances() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
  }


  CmpiStatus SUSE_HostedInstallationServiceProviderClass::getInstance( const CmpiContext &ctx, CmpiResult &rslt, const CmpiObjectPath &cop, const char **properties )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI GetInstance() called",_ClassName));

    CmpiInstance ci = assoc_get_inst( *broker, ctx, cop, _ClassName, _RefLeft, _RefRight);

    rslt.returnData( ci );
    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI GetInstance() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
  }



  CmpiStatus SUSE_HostedInstallationServiceProviderClass::associators( const CmpiContext& ctx, CmpiResult& rslt,
      const CmpiObjectPath& cop, const char* assocClass, const char* resultClass,
      const char* role, const char* resultRole, const char** properties )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI associators() called",_ClassName));

    CmpiObjectPath op( cop.getNameSpace(), _ClassName );

    if ( !assocClass || op.classPathIsA( assocClass ) )
    {
      if ( assoc_check_parameter_const( cop, _RefLeft, _RefRight, _RefLeftClass, _RefRightClass,
                                        resultClass, role, resultRole ) )
      {
        SUSE_HostedInstallationServiceFilter filter(get_this_computersystem(*broker, ctx, cop));
        if(! assoc_create_refs_1toN( *broker, ctx, rslt, cop, _ClassName,
                                     _RefLeft, _RefRight, _RefLeftClass, _RefRightClass, 1, 1, filter ) )
        {
          CmpiStatus st(CMPI_RC_ERR_FAILED, "Create references failed.");
          _CMPIZYPP_TRACE(1,("--- CMPI referenceNames() failed."));
          return st;
        }
      }
    }

    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI associators() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
   }

  CmpiStatus SUSE_HostedInstallationServiceProviderClass::associatorNames( const CmpiContext& ctx, CmpiResult& rslt,
      const CmpiObjectPath& cop, const char* assocClass, const char* resultClass,
      const char* role, const char* resultRole )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI associatorNames() called",_ClassName));

    CmpiObjectPath op( cop.getNameSpace(), _ClassName );

    if ( !assocClass || op.classPathIsA( assocClass ) )
    {
      if ( assoc_check_parameter_const( cop, _RefLeft, _RefRight, _RefLeftClass, _RefRightClass,
                                        resultClass, role, resultRole ) )
      {
        SUSE_HostedInstallationServiceFilter filter(get_this_computersystem(*broker, ctx, cop));
        if(! assoc_create_refs_1toN( *broker, ctx, rslt, cop, _ClassName,
                                     _RefLeft, _RefRight, _RefLeftClass, _RefRightClass, 0, 1, filter ) )
        {
          CmpiStatus st(CMPI_RC_ERR_FAILED, "Create references failed.");
          _CMPIZYPP_TRACE(1,("--- CMPI referenceNames() failed."));
          return st;
        }
      }
    }

    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI associatorNames() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
  }

  CmpiStatus SUSE_HostedInstallationServiceProviderClass::references( const CmpiContext& ctx, CmpiResult& rslt,
      const CmpiObjectPath& cop, const char* resultClass, const char* role,
      const char** properties )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI references() called",_ClassName));

    CmpiObjectPath op( cop.getNameSpace(), _ClassName );

    if ( !resultClass || op.classPathIsA( resultClass ) )
    {
      if ( assoc_check_parameter_const( cop, _RefLeft, _RefRight, _RefLeftClass, _RefRightClass,
                                        NULL/*resultClass*/, role, NULL /*resultRole*/ ) )
      {
        SUSE_HostedInstallationServiceFilter filter(get_this_computersystem(*broker, ctx, cop));
        if(! assoc_create_refs_1toN( *broker, ctx, rslt, cop, _ClassName,
                                     _RefLeft, _RefRight, _RefLeftClass, _RefRightClass, 1, 0, filter ) )
        {
          CmpiStatus st(CMPI_RC_ERR_FAILED, "Create references failed.");
          _CMPIZYPP_TRACE(1,("--- CMPI referenceNames() failed."));
          return st;
        }
      }
    }

    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI references() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
  }

  CmpiStatus SUSE_HostedInstallationServiceProviderClass::referenceNames( const CmpiContext& ctx, CmpiResult& rslt,
      const CmpiObjectPath& cop, const char* resultClass, const char* role )
  {
    _CMPIZYPP_TRACE(1,("--- %s CMPI referenceNames() called",_ClassName));

    CmpiObjectPath op( cop.getNameSpace(), _ClassName );

    if ( !resultClass || op.classPathIsA( resultClass ) )
    {
      if ( assoc_check_parameter_const( cop, _RefLeft, _RefRight, _RefLeftClass, _RefRightClass,
                                        NULL/*resultClass*/, role, NULL /*resultRole*/ ) )
      {
        SUSE_HostedInstallationServiceFilter filter(get_this_computersystem(*broker, ctx, cop));
        if(! assoc_create_refs_1toN( *broker, ctx, rslt, cop, _ClassName,
                                     _RefLeft, _RefRight, _RefLeftClass, _RefRightClass, 0, 0, filter ) )
        {
          CmpiStatus st(CMPI_RC_ERR_FAILED, "Create references failed.");
          _CMPIZYPP_TRACE(1,("--- CMPI referenceNames() failed."));
          return st;
        }
      }
    }

    rslt.returnDone();
    _CMPIZYPP_TRACE(1,("--- %s CMPI referenceNames() exited",_ClassName));
    return CmpiStatus(CMPI_RC_OK);
 }

/* -------------------------------------------------------------------------- */

 SUSE_HostedInstallationServiceFilter::SUSE_HostedInstallationServiceFilter(const CmpiObjectPath &op)
 : SUSE_AssocFilter()
 , csop(op)
 { }

 bool SUSE_HostedInstallationServiceFilter::filterInstance(const CmpiObjectPath &scop, const char * _RefSource, const CmpiInstance &ci, bool associators) const
 {
    _CMPIZYPP_TRACE(1,("--- SUSE_HostedInstallationServiceFilter::filterInstance called"));
    return filterObjectPath( scop, _RefSource, ci.getObjectPath(), associators );

 }

 bool SUSE_HostedInstallationServiceFilter::filterObjectPath(const CmpiObjectPath &scop, const char * _RefSource, const CmpiObjectPath &op, bool associators) const
 {
    _CMPIZYPP_TRACE(1,("--- SUSE_HostedInstallationServiceFilter::filterObjectPath called"));
    USR << scop << " " <<_RefSource << ": " <<  op << endl;

    CmpiString CSName = csop.getKey("CreationClassName");
    CmpiString Name = csop.getKey("Name");

    const char *filterCSName = "";
    const char *filterName   = "";
    if( ! associators )
    {
      CmpiObjectPath filterop = op.getKey( _RefLeft );
      filterCSName = filterop.getKey("CreationClassName");
      filterName   = filterop.getKey("Name");
    }
    else
    {
      if ( ::strcmp(_RefSource, _RefLeft ) != 0 )
      {
        filterCSName = op.getKey("CreationClassName");
        filterName   = op.getKey("Name");
      }
      else
      {
        filterCSName = scop.getKey("CreationClassName");
        filterName   = scop.getKey("Name");
      }
    }

    if(CSName.equals(filterCSName) && Name.equals(filterName) )
    {
      _CMPIZYPP_TRACE(1,("--- SUSE_HostedInstallationServiceFilter::filterInstance exited: true"));
      return true;
    }
    else
    {
      _CMPIZYPP_TRACE(1,("--- SUSE_HostedInstallationServiceFilter::filterInstance exited: false"));
      return false;
    }
}

} // namespace cmpizypp

CMProviderBase( SUSE_HostedInstallationServiceProvider );

CMInstanceMIFactory( cmpizypp::SUSE_HostedInstallationServiceProviderClass, SUSE_HostedInstallationServiceProvider );
CMAssociationMIFactory( cmpizypp::SUSE_HostedInstallationServiceProviderClass, SUSE_HostedInstallationServiceProvider );
