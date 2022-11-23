#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arch.h>
#include <arch_printer.h>

void print_core(FILE *fp, struct arch_core *c)
{
	struct arch_function *tmp = c->stream_functions;

	while (tmp != (struct arch_function *)0)
	{
		fprintf(fp, "%s_point [shape=point,style=invis]\n", tmp->in_name);
		fprintf(fp, "%s_point [shape=point,style=invis]\n", tmp->out_name);
		tmp = tmp->next;
	}

	fprintf(fp, "\tsubgraph cluster_%s{\n", c->name);

	fprintf(fp, "\t\tstyle=filled;\n");

	fprintf(fp, "\t\tlabel = \"%s\";\n", c->name);

	if (c->main_function != (struct arch_function *)0)
	{
		fprintf(fp, "%s_main [shape=box,label=\"main\"]\n", c->name);
	}
	if (c->signal_function != (struct arch_function *)0)
	{
		fprintf(fp, "%s_signal [shape=box,label=\"signal\"]\n", c->name);
	}
	tmp = c->stream_functions;
	int i = 0;

	while (tmp != (struct arch_function *)0)
	{
		// fprintf(fp,"%s_point [shape=point,style=invis]\n",tmp->in_name);
		fprintf(fp, "%s_stream%d [shape=box,label=\"stream\"]\n", c->name, i);
		// fprintf(fp,"%s_point -> %s_stream [label=\"%s()\"]\n",tmp->in_name,c->name,tmp->in_name);
		tmp = tmp->next;
		i++;
	}

	fprintf(fp, "\t}\n");

	tmp = c->stream_functions;

	i = 0;
	while (tmp != (struct arch_function *)0)
	{
		// fprintf(fp,"%s_point [shape=point,style=invis]\n",tmp->in_name);
		// fprintf(fp,"%s_stream [shape=box,label=\"stream\"]\n",c->name);
		fprintf(fp, "%s_point -> %s_stream%d [label=\"%s()\"]\n", tmp->in_name, c->name, i, tmp->in_name);
		fprintf(fp, "%s_stream%d -> %s_point [label=\"%s()\"]\n", c->name, i, tmp->out_name, tmp->out_name);
		tmp = tmp->next;
		i++;
	}
}

void print_arch(struct arch *my_arch)
{
	FILE *fp;
	fp = fopen("structures/arch.dot", "w");

	fprintf(fp, "digraph arch {\n");

	// fprintf(fp,"NULL_node [style=invis,shape=point]\n");

	struct arch_core *c = my_arch->arch_cores;
	// print graph

	while (c != (struct arch_core *)0)
	{
		print_core(fp, c);
		c = c->next;
	}

	/*c = my_arch->arch_cores;

	while(c != (struct core *)0)
	{
		fprintf(fp,"NULL_node -> %s_main\n",c->name);
		c = c->next;
	}*/

	fprintf(fp, "}\n");

	fclose(fp);
	system("dot -Tpng structures/arch.dot > structures/arch.png");
}