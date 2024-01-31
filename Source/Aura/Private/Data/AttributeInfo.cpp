#include "Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo & CurAttributeInfo : AuraAttributeInfos)
	{
		if (CurAttributeInfo.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return CurAttributeInfo;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find for AttributeTag."));
	}

	return FAuraAttributeInfo();
}
