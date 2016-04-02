#ifndef WIERTLO_PIMPL_HANDLE_HPP_D368EE33A8A1449B8725F85313045623
#define WIERTLO_PIMPL_HANDLE_HPP_D368EE33A8A1449B8725F85313045623

#include <cstddef>
#include <memory>
#include <utility>
#include <type_traits>

namespace wiertlo
{
	template<typename PimplHandle, typename HandleType, typename ImplType>
	class pimpl_implementation_mixin;
	
	template<typename PimplImplementation, typename Type = void*, std::size_t Count = 1, std::size_t Alignment = alignof(Type)>
	class pimpl_handle
	{
		alignas(Alignment) char buffer[Count*sizeof(Type)];
		
		pimpl_handle() {}
		
	public:
		template<typename PimplHandle, typename ImplType, typename HandleType>
		friend class pimpl_implementation_mixin;
		
		pimpl_handle(const pimpl_handle& other)
		{
			PimplImplementation::copy_constructor(*this, other);
		}
		
		pimpl_handle(pimpl_handle&& other) noexcept
		{
			PimplImplementation::move_constructor(*this, std::move(other));
		}
		
		pimpl_handle& operator=(const pimpl_handle& other)
		{
			PimplImplementation::copy_assignment_operator(*this, other);
			return *this;
		}
		
		pimpl_handle& operator=(pimpl_handle&& other) noexcept
		{
			PimplImplementation::move_assignment_operator(*this, std::move(other));
			return *this;
		}
		
		~pimpl_handle()
		{
			PimplImplementation::destructor(*this);
		}
	};
	
	template<typename PimplHandle, typename ImplType, typename HandleType = std::unique_ptr<ImplType>>
	class pimpl_implementation_mixin
	{
	private:
		static_assert(sizeof(PimplHandle) >= sizeof(HandleType), "size is incorrect");
		static_assert(alignof(PimplHandle) >= alignof(HandleType), "alignment is incorrect");
		
		template<typename PimplImplementation, typename Type, std::size_t Count, std::size_t Alignment>
		friend class pimpl_handle;
		
		static void copy_constructor(PimplHandle& me, const PimplHandle& other)
		{
			::new(static_cast<void*>(&me.buffer))
				HandleType(get_handle(other));
		}
		
		static void move_constructor(PimplHandle& me, PimplHandle&& other)
		{
			::new(static_cast<void*>(&me.buffer))
				HandleType(std::move(get_handle(other)));
		}
		
		static void move_assignment_operator(PimplHandle& me, PimplHandle&& other)
		{
			get_handle(me) = std::move(get_handle(other));
		}
		
		static void copy_assignment_operator(PimplHandle& me, const PimplHandle& other)
		{
			get_handle(me) = get_handle(other);
		}
		
		static void destructor(PimplHandle& me)
		{
			get_handle(me).~HandleType();
		}
		
	public:
		typedef PimplHandle pimpl_handle_type;
		typedef HandleType handle_type;
		typedef ImplType impl_type;
		
		static const HandleType& get_handle(const pimpl_handle_type& pimpl)
		{
			return *reinterpret_cast<const HandleType*>(pimpl.buffer);
		}
		
		static HandleType& get_handle(pimpl_handle_type& pimpl)
		{
			return *reinterpret_cast<HandleType*>(pimpl.buffer);
		}
		
		static impl_type& get(pimpl_handle_type& handle) { return *get_handle(handle); }

		template<typename... Args>
		static pimpl_handle_type create_pimpl_handle(Args&&... args)
		{
			pimpl_handle_type h;
			::new(static_cast<void*>(&h.buffer))
				HandleType(std::forward<Args>(args)...);
			return h;
		}
	};

}

#endif