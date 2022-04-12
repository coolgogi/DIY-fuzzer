while ((dir_info = readdir(dir))) {
			
			if (dir_info->d_name[0] == '.')
				continue ;

			if (dir_info->d_type == DT_DIR)
				continue ;
				
			int tp_branch[num_of_branch + 1] ;
			memset(tp_branch, 0, sizeof(int) * (num_of_branch + 1)) ;
			
			char * bcov_file = (char *) malloc (strlen(outputDir_path) + strlen(dir_info->d_name)) ;
			strcpy(bcov_file, outputDir_path) ;
			strcat(bcov_file, dir_info->d_name) ;
		
			struct stat st ;
			stat(bcov_file, &st) ;

			unsigned int file_size = st.st_size ;
			int n = file_size / (sizeof(uint32_t) + 1024)  ;

			FILE * bcov_ptr = fopen(bcov_file, "r") ;

			uint32_t * buf = (uint32_t *) malloc (sizeof(uint32_t)) ;
			uint32_t * size = (uint32_t *) malloc (sizeof(uint32_t)) ;
			char * PcDescr = (char *) malloc (1024) ;
			
			while (file_size > 1) {
				fread(buf, 1, sizeof(uint32_t), bcov_ptr) ;
				file_size = file_size - sizeof(uint32_t) ;
				fread(size, 1, sizeof(uint32_t), bcov_ptr) ;
				file_size = file_size - sizeof(uint32_t) ;
				fread(PcDescr, 1, *size, bcov_ptr) ;
				file_size = file_size - *size ;
				
				if (tp_branch[*buf] != 1) {
					tp_branch[*buf] = 1 ;
					strcpy(branch_path[*buf], PcDescr) ;
				}

			}

			free(PcDescr) ;
			free(size) ;
			free(buf) ;

			char * ch = (char *) malloc (1) ;
			fread(ch, 1, 1, bcov_ptr) ;
			if (*ch == 'p') {
				rt[0] ++ ;
			}
			else if (*ch == 't') {
				rt[1] ++ ;
				timeout ++ ;
			}
			else if (*ch == 'f') {
				rt[1] ++ ;
			}
			
			for (int i = 1 ; i < num_of_branch + 1 ; i ++) {
				if (tp_branch[i] == 1) {

					if (*ch == 'p') {
						p_branch[i] ++ ;
					}
					else  {	
						f_branch[i] ++ ;
					}
				}
			}
			
			free(bcov_file) ;
			free(ch) ;
			fclose(bcov_ptr) ;
			
		}
