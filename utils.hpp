#ifndef __ILRD_RD_133_4_ILRD_UTILS__
#define __ILRD_RD_133_4_ILRD_UTILS__

namespace ilrd
{
class noncopyable
{
protected:
  constexpr noncopyable() = default;
  noncopyable(const noncopyable&) = delete;
  noncopyable& operator=(const noncopyable&) =delete;
};
}
#endif