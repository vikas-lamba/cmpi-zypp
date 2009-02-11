#ifndef SUSE_REPOSITORYAVAILABLEFORSOFTWAREIDENTITYPROVIDERCLASS_H
#define SUSE_REPOSITORYAVAILABLEFORSOFTWAREIDENTITYPROVIDERCLASS_H

#include <cmpi/CmpiInstanceMI.h>
#include <cmpi/CmpiAssociationMI.h>

namespace cmpizypp
{
  /**
  */
  class SUSE_RepositoryAvailableForSoftwareIdentityProviderClass : public CmpiInstanceMI, public CmpiAssociationMI
  {
    public:
      SUSE_RepositoryAvailableForSoftwareIdentityProviderClass( const CmpiBroker & mbp, const CmpiContext & ctx );

      virtual CmpiStatus enumInstanceNames( const CmpiContext& ctx, CmpiResult& rslt, const CmpiObjectPath & cop );
      virtual CmpiStatus enumInstances( const CmpiContext & ctx, CmpiResult & rslt, const CmpiObjectPath & cop, const char** properties );
      virtual CmpiStatus getInstance( const CmpiContext &ctx, CmpiResult &rslt, const CmpiObjectPath &cop, const char **properties );

      virtual CmpiStatus associators
          (const CmpiContext& ctx, CmpiResult& rslt,
           const CmpiObjectPath& cop, const char* assocClass, const char* resultClass,
           const char* role, const char* resultRole, const char** properties);

      virtual CmpiStatus associatorNames
          (const CmpiContext& ctx, CmpiResult& rslt,
           const CmpiObjectPath& cop, const char* assocClass, const char* resultClass,
           const char* role, const char* resultRole);

      virtual CmpiStatus references
          (const CmpiContext& ctx, CmpiResult& rslt,
           const CmpiObjectPath& cop, const char* resultClass, const char* role,
           const char** properties);

      virtual CmpiStatus referenceNames
          (const CmpiContext& ctx, CmpiResult& rslt,
           const CmpiObjectPath& cop, const char* resultClass, const char* role);
  };
} // namespace cmpizypp

#endif // SUSE_REPOSITORYAVAILABLEFORSOFTWAREIDENTITYPROVIDERCLASS_H
