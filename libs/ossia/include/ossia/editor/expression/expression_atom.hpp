#pragma once

#include <memory>

#include <ossia/editor/expression/expression_fwd.hpp>
#include <ossia/editor/value/value.hpp>

#include <ossia/network/base/address.hpp>
#include <ossia_export.h>

namespace ossia
{
namespace expressions
{
/**
 * @brief expression_atom : numeric operators in expressions.
 * @see expression.hpp
 */
class OSSIA_EXPORT expression_atom final :
    public expression_callback_container
{
public:
  enum class Comparator
  {
    EQUAL,  //! ==
    DIFFERENT, //! !=
    GREATER_THAN, //! >
    LOWER_THAN, //! <
    GREATER_THAN_OR_EQUAL, //! >=
    LOWER_THAN_OR_EQUAL //! <=
  };

  expression_atom(
      const value& lhs, Comparator op = Comparator::EQUAL,
      const value& rhs = Impulse{});
  expression_atom(expression_atom&& other) = delete;
  expression_atom& operator=(expression_atom&& other) = delete;

  expression_atom(const expression_atom& other) = delete;
  expression_atom& operator=(const expression_atom& other) = delete;

  virtual ~expression_atom();

  bool evaluate() const;
  void update() const;

  const value& getFirstOperand() const;
  Comparator getOperator() const;
  const value& getSecondOperand() const;

private:
  void onFirstCallbackAdded() override;
  void onRemovingLastCallback() override;

  bool do_evaluation(const value& first, const value& second) const;

  void firstValueCallback(const ossia::value& value);
  void secondValueCallback(const ossia::value& value);

  ossia::value mFirstValue;
  ossia::value mSecondValue;

  net::address_base::callback_index mFirstValueCallbackIndex;
  net::address_base::callback_index mSecondValueCallbackIndex;

  Comparator mOperator;
};
}
}
