/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:44:03 by mateo             #+#    #+#             */
/*   Updated: 2024/04/02 19:28:40 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_gnl_list
{
	struct s_gnl_list	*next;
	struct s_gnl_list	*prev;
	char			*str;
	int				nl;
	int				eof;
}	t_gnl_list;

typedef struct s_gnl
{
	int fd;
	int free_static;
	int read_r;
	char *newline;
}	t_gnl;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);

int			ft_toupper(int c);
int			ft_tolower(int c);

void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
char		*ft_strdup(const char *src);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c, char d);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// void		*ft_gnl_lstclear(t_gnl_list **head, int clear);
// t_gnl_list	*ft_lstaddnew(t_gnl_list **head, int blank);
// t_gnl_list	*ft_lstsplit(t_gnl_list *last, char *newline);
// int			ft_lststrlen(t_gnl_list *head, t_gnl_list *last);


// char		*ft_lststrcat(int len, t_gnl_list **head, char *fullline);
// char		*ft_lststrcat_setup(t_gnl_list **head, t_gnl_list *last);
// t_gnl_meta*	ft_gnl_meta(int fd, int free_static, t_gnl_list **head);
// // char		*gnl_setup(int fd, char **newline, int *read_r, t_gnl_list **head);
// char		*get_next_line(int fd, int free_static);

// new 
// void		*ft_gnl_lstclear(t_gnl_list **head, int clear); 
void	*ft_gnl_lstclear(t_gnl_list **lst, int forward, t_gnl *meta);
t_gnl_list	*ft_lstaddnew(t_gnl_list **head, int blank);
t_gnl_list	*ft_lstsplit(t_gnl_list *last, char *newline);
int			ft_lststrlen(t_gnl_list *head, t_gnl_list *last);


char	*ft_lststrcat(int len, t_gnl_list **head, char *fullline, t_gnl *meta);
char	*ft_lststrcat_setup(t_gnl_list **head, t_gnl_list *last, t_gnl *meta);

// char		*ft_lststrcat(int len, t_gnl_list **head, char *fullline);
// char		*ft_lststrcat_setup(t_gnl_list **head, t_gnl_list *last);
t_gnl*	ft_gnl_meta(int fd, int free_static, t_gnl_list **head);
char		*get_next_line(int fd, int free_static);

#endif
