template<typename T>
void sswap(T pa, T pb)
{
    auto const copy = *pa;
    *pa = *pb;
    *pb = copy;
}

template<typename T, typename Pred>
T *partition(T *begin, T *end, Pred predicate){
	//int len = end - begin;
	T *left = begin;
	int right = 0;
	while((left - begin) + right < end - begin){
		if(predicate(left) == 0 && predicate(begin + (end - begin - right - 1)) == 1){
			sswap(left, end - right - 1);
			//left ++;
			//right ++;
		}else if(predicate(left) == 1){
			left ++;
		}else if(predicate(begin + (end - begin - right - 1)) == 0){
			right ++;
		}
	}
	return left;
}

template<typename T>
void quicksort(T *begin, T *end, bool cmp()){
	if(end - begin > 1){
		auto leseq = [begin, cmp](T *x){return cmp(*x, *begin);};
		T *pos = partition(begin, end, leseq);
		//sswap(begin, pos);
		// std::cout << *pos << " ";
		// std::cout << *begin << " " << end[-1] << " ";
		// for(int i = 0; i < end - begin; i++){
		// 	std::cout << begin[i];
		// }
		// std::cout << std::endl;
		sswap(begin, pos);
		
		if(pos - begin > 1){
			// std::cout << "left" << std::endl;
			quicksort(begin, pos, cmp);
		}
		if(end - pos > 2){
			// std::cout << "right" << std::endl;
			// for (int i = 0; i < end - pos; ++i)
			// {
			// 	std::cout << begin[i] << "; ";
			// }
			// std::cout << std::endl;
			quicksort(pos + 1, end, cmp);
		}
	}
}