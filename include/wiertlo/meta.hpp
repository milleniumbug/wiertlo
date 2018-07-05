#ifndef HEADER5796e875d78218a7f939504debe77971
#define HEADER5796e875d78218a7f939504debe77971

#include <type_traits>

namespace wiertlo
{
	namespace meta
	{
		namespace detail
		{
			template<typename T>
			struct identity { typedef T type; };
		}

		template<typename... Types>
		struct TypeList
		{};

		template<typename... Args>
		using Void = void;

		template<typename T>
		using SuppressTemplateDeduction = typename detail::identity<T>::type;

		template<typename T>
		using Lazy = detail::identity<T>;

		namespace detail
		{
			template<typename Type, std::size_t Index, typename... Args>
			struct FindImpl;

			template<typename Type, std::size_t Index>
			struct FindImpl<Type, Index>;

			template<typename Type, std::size_t Index, typename Head, typename... Tail>
			struct FindImpl<Type, Index, Head, Tail...> : std::conditional<
				(std::is_same<Type, Head>::value),
				std::integral_constant<std::size_t, Index>,
				FindImpl<Type, Index+1, Tail...>
			>::type
			{

			};

			template<template<typename...> class MetaUnaryPredicate, std::size_t Index, typename... Args>
			struct FindIfImpl;

			template<template<typename...> class MetaUnaryPredicate, std::size_t Index>
			struct FindIfImpl<MetaUnaryPredicate, Index>;

			template<template<typename...> class MetaUnaryPredicate, std::size_t Index, typename Head, typename... Tail>
			struct FindIfImpl<MetaUnaryPredicate, Index, Head, Tail...> : std::conditional<
				(MetaUnaryPredicate<Head>::value),
				std::integral_constant<std::size_t, Index>,
				FindIfImpl<MetaUnaryPredicate, Index+1, Tail...>
			>::type
			{

			};

			template<std::size_t Index, std::size_t Current, typename... Args>
			struct TypeAtImpl;

			template<std::size_t Index, std::size_t Current>
			struct TypeAtImpl<Index, Current>;

			template<std::size_t Index, std::size_t Current, typename Head, typename... Tail>
			struct TypeAtImpl<Index, Current, Head, Tail...> : std::conditional<
				Index == Current,
				Lazy<Head>,
				TypeAtImpl<Index, Current+1, Tail...>
			>::type
			{

			};

			template<typename... TypeLists>
			struct ConcatImpl;

			template<typename... Args1, typename... Args2>
			struct ConcatImpl<TypeList<Args1...>, TypeList<Args2...>>
			{
				typedef TypeList<Args1..., Args2...> type;
			};

			template<typename TypeList1, typename TypeList2>
			struct ReverseImpl;

			template<typename Head2, typename... Tail2, typename... Types1>
			struct ReverseImpl<TypeList<Types1...>, TypeList<Head2, Tail2...>>
			{
				typedef typename ReverseImpl<TypeList<Head2, Types1...>, TypeList<Tail2...>>::type type;
			};

			template<typename... Types1>
			struct ReverseImpl<TypeList<Types1...>, TypeList<>>
			{
				typedef TypeList<Types1...> type;
			};
		}

		template<typename TypeList>
		struct Length;

		template<typename... Args>
		struct Length<TypeList<Args...>> : std::integral_constant<std::size_t, sizeof...(Args)>
		{
			
		};

		template<typename TypeList, typename Type>
		struct Contains;

		template<typename Type>
		struct Contains<TypeList<>, Type> : std::false_type
		{
			
		};

		template<typename Type, typename Head, typename... Tail>
		struct Contains<TypeList<Head, Tail...>, Type> : std::conditional<
			(std::is_same<Type, Head>::value || Contains<TypeList<Tail...>, Type>::value),
			std::true_type,
			std::false_type
		>::type
		{
			
		};

		template<typename TypeList, typename Type>
		struct Find;

		template<typename Type, typename... Args>
		struct Find<TypeList<Args...>, Type> : detail::FindImpl<Type, 0, Args...>
		{

		};

		template<typename TypeList, template<typename...> class MetaUnaryPredicate>
		struct FindIf;

		template<template<typename...> class MetaUnaryPredicate, typename... Args>
		struct FindIf<TypeList<Args...>, MetaUnaryPredicate> : detail::FindIfImpl<MetaUnaryPredicate, 0, Args...>
		{

		};

		template<std::size_t Index, typename TypeList>
		struct TypeAt;

		template<std::size_t Index, typename... Args>
		struct TypeAt<Index, TypeList<Args...>> : detail::TypeAtImpl<Index, 0, Args...>
		{

		};

		template<template<typename...> class UnaryMetaFunction, typename TypeList>
		struct Map;

		template<template<typename...> class UnaryMetaFunction, typename... Args>
		struct Map<UnaryMetaFunction, TypeList<Args...>>
		{
			typedef TypeList<typename UnaryMetaFunction<Args>::type...> type;
		};

		template<template<typename...> class BinaryMetaFunction, typename First, typename TypeList>
		struct Reduce;

		template<template<typename...> class BinaryMetaFunction, typename First>
		struct Reduce<BinaryMetaFunction, First, TypeList<>>
		{
			typedef First type;
		};

		template<template<typename...> class BinaryMetaFunction, typename Head, typename... Tail, typename First>
		struct Reduce<BinaryMetaFunction, First, TypeList<Head, Tail...>>
		{
			typedef typename Reduce<BinaryMetaFunction, typename BinaryMetaFunction<First, Head>::type, TypeList<Tail...>>::type type;
		};

		template<template<typename...> class BinaryMetaFunction, typename TypeList>
		struct Reduce1;

		template<template<typename...> class BinaryMetaFunction, typename Head, typename... Tail>
		struct Reduce1<BinaryMetaFunction, TypeList<Head, Tail...>>
		{
			typedef typename Reduce<BinaryMetaFunction, Head, TypeList<Tail...>>::type type;
		};

		template<typename... TypeLists>
		struct Concat
		{
			typedef typename Reduce<detail::ConcatImpl, TypeList<>, TypeList<TypeLists...>>::type type;
		};

		template<template<typename...> class UnaryPredicate, typename TypeList>
		struct Filter;

		template<template<typename...> class UnaryPredicate>
		struct Filter<UnaryPredicate, TypeList<>>
		{
			typedef TypeList<> type;
		};

		template<template<typename...> class UnaryPredicate, typename Head>
		struct Filter<UnaryPredicate, TypeList<Head>>
		{
			typedef typename std::conditional<
				UnaryPredicate<Head>::value,
				TypeList<Head>,
				TypeList<>>::type type;
		};

		template<template<typename...> class UnaryPredicate, typename Head, typename... Tail>
		struct Filter<UnaryPredicate, TypeList<Head, Tail...>>
		{
			typedef typename Concat<
				typename Filter<UnaryPredicate, TypeList<Head>>::type,
				typename Filter<UnaryPredicate, TypeList<Tail...>>::type
			>::type type;
		};

		namespace detail
		{
			template<template<typename...> class UnaryMetaFunction, typename Value, std::size_t Index, std::size_t N>
			struct IterateNImpl
			{
				typedef typename Concat<
					TypeList<Value>,
					typename IterateNImpl<
						UnaryMetaFunction,
						typename UnaryMetaFunction<Value>::type,
						Index+1,
						N
					>::type
				>::type type;
			};

			template<template<typename...> class UnaryMetaFunction, typename Value, std::size_t N>
			struct IterateNImpl<UnaryMetaFunction, Value, N, N>
			{
				typedef TypeList<> type;
			};

			template<typename Number>
			struct IncrementImpl;

			template<typename T, T N>
			struct IncrementImpl<std::integral_constant<T, N>>
			{
				typedef std::integral_constant<T, N+1> type;
			};
		}

		template<template<typename...> class UnaryMetaFunction, typename Value, std::size_t N>
		struct IterateN
		{
			typedef typename detail::IterateNImpl<
				UnaryMetaFunction,
				Value,
				0,
				N
			>::type type;
		};

		template<typename T, T N>
		struct Iota
		{
			typedef typename IterateN<detail::IncrementImpl, std::integral_constant<T, 0>, N>::type type;
		};

		template<typename TypeList>
		struct Front
		{
			typedef typename TypeAt<0, TypeList>::type type;
		};

		template<typename TypeList>
		struct Back
		{
			typedef typename TypeAt<Length<TypeList>::value-1, TypeList>::type type;
		};

		template<typename TypeList, typename What>
		struct PushBack;

		template<typename... Args, typename What>
		struct PushBack<TypeList<Args...>, What>
		{
			typedef TypeList<Args..., What> type;
		};

		template<typename TypeList, typename What>
		struct PushFront;

		template<typename... Args, typename What>
		struct PushFront<TypeList<Args...>, What>
		{
			typedef TypeList<What, Args...> type;
		};

		template<typename TypeList>
		struct PopFront;

		template<typename Head, typename... Tail>
		struct PopFront<TypeList<Head, Tail...>>
		{
			typedef TypeList<Tail...> type;
		};

		template<typename List>
		struct Reverse
		{
			typedef typename detail::ReverseImpl<TypeList<>, List>::type type;
		};

		template<typename List>
		struct PopBack
		{
		private:
			typedef typename Reverse<List>::type first_;
			typedef typename PopFront<first_>::type second_;
			typedef typename Reverse<second_>::type third_;
		public:
			typedef third_ type;
		};

		template<typename From, typename To>
		struct CopyCv
		{
			typedef To type;
		};

		template<typename From, typename To>
		struct CopyCv<const From, To>
		{
			typedef const To type;
		};

		template<typename From, typename To>
		struct CopyCv<volatile From, To>
		{
			typedef volatile To type;
		};

		template<typename From, typename To>
		struct CopyCv<const volatile From, To>
		{
			typedef const volatile To type;
		};
	}
}

#endif