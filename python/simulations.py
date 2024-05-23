# Default simulation library containing:
# - Basic [project]ion simulations (convergence for different beta, etc)
# - Merge simulations (different betas)
# - Pattern completion simulations
# - Association simulations
# - simulations studying density in assemblies (higher than ambient p)

# Also contains methods for plotting saved results from some of these simulations
# (for figures).

import brain
import brain_util as bu
import numpy as np
import random
import copy
import pickle
import matplotlib.pyplot as plt

from collections import OrderedDict


def project_sim(n=1000000,k=1000,p=0.01,beta=0.05,t=50):
	b = brain.Brain(p)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	for i in range(t-1):
		b.project({"stim":["A"]},{"A":["A"]})
	return b.areas["A"].saved_w


def project_beta_sim(n=100000,k=317,p=0.01,t=100):
	results = {}
	for beta in [0.25,0.1,0.075,0.05,0.03,0.01,0.007,0.005,0.003,0.001]:
		print("Working on " + str(beta) + "\n")
		out = project_sim(n,k,p,beta,t)
		results[beta] = out
	return results

def assembly_only_sim(n=100000,k=317,p=0.05,beta=0.05,project_iter=10):
	b = brain.Brain(p)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	for i in range(project_iter-1):
		b.project({"stim":["A"]},{"A":["A"]})
	for i in range(5):
		b.project({},{"A":["A"]})
	return b.areas["A"].saved_w


# alpha = percentage of (random) final assembly neurons to try firing
def pattern_com(n=100000,k=317,p=0.05,beta=0.05,project_iter=10,alpha=0.5,comp_iter=1):
	b = brain.Brain(p,save_winners=True)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	for i in range(project_iter-1):
		b.project({"stim":["A"]},{"A":["A"]})
	# pick random subset of the neurons to fire
	subsample_size = int(k*alpha)
	subsample = random.sample(b.areas["A"].winners, subsample_size)
	b.areas["A"].winners = subsample
	for i in range(comp_iter):
		b.project({},{"A":["A"]})
	return b.areas["A"].saved_w,b.areas["A"].saved_winners

def pattern_com_repeated(n=100000,k=317,p=0.05,beta=0.05,project_iter=12,alpha=0.4,
	trials=3, max_recurrent_iter=10, resample=False):
	b = brain.Brain(p,save_winners=True)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	for i in range(project_iter-1):
		b.project({"stim":["A"]},{"A":["A"]})

	subsample_size = int(k*alpha)
	rounds_to_completion = []
	# pick random subset of the neurons to fire
	subsample = random.sample(b.areas["A"].winners, subsample_size)
	for trail in range(trials):
		if resample:
			subsample = random.sample(b.areas["A"].winners, subsample_size)
		b.areas["A"].winners = subsample
		rounds = 0
		while True:
			rounds += 1
			b.project({},{"A":["A"]})
			if (b.areas["A"].num_first_winners == 0) or (rounds == max_recurrent_iter):
				break
		rounds_to_completion.append(rounds)
	saved_winners = b.areas["A"].saved_winners
	overlaps = bu.get_overlaps(saved_winners,project_iter-1,percentage=True)
	return overlaps, rounds_to_completion

def pattern_com_alphas(n=100000,k=317,p=0.01,beta=0.05,
	alphas=[0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0],project_iter=25,comp_iter=5):
	b = brain.Brain(p)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	for i in range(project_iter-1):
		b.project({"stim":["A"]},{"A":["A"]})
	results = {}
	A_winners = b.areas["A"].winners
	for alpha in alphas:
		# pick random subset of the neurons to fire
		subsample_size = int(k*alpha)
		b_copy = copy.deepcopy(b)
		subsample = random.sample(b_copy.areas["A"].winners, subsample_size)
		b_copy.areas["A"].winners = subsample
		for i in range(comp_iter):
			b_copy.project({},{"A":["A"]})
		final_winners = b_copy.areas["A"].winners
		o = bu.overlap(final_winners, A_winners)
		results[alpha] = float(o)/float(k)
	return results

def pattern_com_iterations(n=100000,k=317,p=0.01,beta=0.05,alpha=0.4,comp_iter=8,
	min_iter=20,max_iter=30):
	b = brain.Brain(p)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	for i in range(min_iter-2):
		b.project({"stim":["A"]},{"A":["A"]})
	results = {}
	subsample_size = int(k*alpha)
	subsample = random.sample(b.areas["A"].winners, subsample_size)
	for i in range(min_iter,max_iter+1):
		b.project({"stim":["A"]},{"A":["A"]})
		b_copy = copy.deepcopy(b)
		b_copy.areas["A"].winners = subsample
		for j in range(comp_iter):
			b_copy.project({},{"A":["A"]})
		o = bu.overlap(b_copy.areas["A"].winners, b.areas["A"].winners)
		results[i] = float(o)/float(k)
	return results

# Sample command c_w,c_winners = bu.association_sim()
def associate(n=100000,k=317,p=0.05,beta=0.1,overlap_iter=10):
	b = brain.Brain(p,save_winners=True)
	b.add_stimulus("stimA",k)
	b.add_area("A",n,k,beta)
	b.add_stimulus("stimB",k)
	b.add_area("B",n,k,beta)
	b.add_area("C",n,k,beta)
	b.project({"stimA":["A"],"stimB":["B"]},{})
	# Create assemblies A and B to stability
	for i in range(9):
		b.project({"stimA":["A"],"stimB":["B"]},
			{"A":["A"],"B":["B"]})
	b.project({"stimA":["A"]},{"A":["A","C"]})
	# Project A->C
	for i in range(9):
		b.project({"stimA":["A"]},
			{"A":["A","C"],"C":["C"]})
	# Project B->C
	b.project({"stimB":["B"]},{"B":["B","C"]})
	for i in range(9):
		b.project({"stimB":["B"]},
			{"B":["B","C"],"C":["C"]})
	# Project both A,B to C
	b.project({"stimA":["A"],"stimB":["B"]},
		{"A":["A","C"],"B":["B","C"]})
	for i in range(overlap_iter-1):
		b.project({"stimA":["A"],"stimB":["B"]},
				{"A":["A","C"],"B":["B","C"],"C":["C"]})
	# Project just B
	b.project({"stimB":["B"]},{"B":["B","C"]})
	for i in range(9):
		b.project({"stimB":["B"]},{"B":["B","C"],"C":["C"]})
	return b

def association_sim(n=100000,k=317,p=0.05,beta=0.1,overlap_iter=10):
	b = associate(n,k,p,beta,overlap_iter)
	return b.areas["C"].saved_w,b.areas["C"].saved_winners

def association_grand_sim(n=100000,k=317,p=0.01,beta=0.05,min_iter=10,max_iter=20):
	b = brain.Brain(p,save_winners=True)
	b.add_stimulus("stimA",k)
	b.add_area("A",n,k,beta)
	b.add_stimulus("stimB",k)
	b.add_area("B",n,k,beta)
	b.add_area("C",n,k,beta)
	b.project({"stimA":["A"],"stimB":["B"]},{})
	# Create assemblies A and B to stability
	for i in range(9):
		b.project({"stimA":["A"],"stimB":["B"]},
			{"A":["A"],"B":["B"]})
	b.project({"stimA":["A"]},{"A":["A","C"]})
	# Project A->C
	for i in range(9):
		b.project({"stimA":["A"]},
			{"A":["A","C"],"C":["C"]})
	# Project B->C
	b.project({"stimB":["B"]},{"B":["B","C"]})
	for i in range(9):
		b.project({"stimB":["B"]},
			{"B":["B","C"],"C":["C"]})
	# Project both A,B to C
	b.project({"stimA":["A"],"stimB":["B"]},
		{"A":["A","C"],"B":["B","C"]})
	for i in range(min_iter-2):
		b.project({"stimA":["A"],"stimB":["B"]},
				{"A":["A","C"],"B":["B","C"],"C":["C"]})
	results = {}
	for i in range(min_iter,max_iter+1):
		b.project({"stimA":["A"],"stimB":["B"]},
				{"A":["A","C"],"B":["B","C"],"C":["C"]})
		b_copy1 = copy.deepcopy(b)
		b_copy2 = copy.deepcopy(b)
		# in copy 1, project just A
		b_copy1.project({"stimA":["A"]},{})
		b_copy1.project({},{"A":["C"]})
		# in copy 2, project just B
		b_copy2.project({"stimB":["B"]},{})
		b_copy2.project({},{"B":["C"]})
		o = bu.overlap(b_copy1.areas["C"].winners, b_copy2.areas["C"].winners)
		results[i] = float(o)/float(k)
	return results

def merge_sim(n=100000,k=317,p=0.01,beta=0.05,max_t=50):
	b = brain.Brain(p)
	b.add_stimulus("stimA",k)
	b.add_stimulus("stimB",k)
	b.add_area("A",n,k,beta)
	b.add_area("B",n,k,beta)
	b.add_area("C",n,k,beta)

	b.project({"stimA":["A"]},{})
	b.project({"stimB":["B"]},{})
	b.project({"stimA":["A"],"stimB":["B"]},
		{"A":["A","C"],"B":["B","C"]})
	b.project({"stimA":["A"],"stimB":["B"]},
		{"A":["A","C"],"B":["B","C"],"C":["C","A","B"]})
	for i in range(max_t-1):
		b.project({"stimA":["A"],"stimB":["B"]},
			{"A":["A","C"],"B":["B","C"],"C":["C","A","B"]})
	return b.areas["A"].saved_w, b.areas["B"].saved_w, b.areas["C"].saved_w

def merge_beta_sim(n=100000,k=317,p=0.01,t=100):
	results = {}
	for beta in [0.3,0.2,0.1,0.075,0.05]:
		print("Working on " + str(beta) + "\n")
		out = merge_sim(n,k,p,beta=beta,max_t=t)
		results[beta] = out
	return results
# UTILS FOR EVAL


def plot_project_sim(show=True, save="", show_legend=False, use_text_font=True):
	results = bu.sim_load('project_results')
	# fonts
	if(use_text_font):
		plt.rcParams['mathtext.fontset'] = 'stix'
		plt.rcParams['font.family'] = 'STIXGeneral'

	# 0.05 and 0.07 overlap almost exactly, pop 0.07
	results.pop(0.007)
	od = OrderedDict(sorted(results.items()))
	x = np.arange(100)
	print(x)
	for key,val in od.iteritems():
		plt.plot(x,val,linewidth=0.7)
	if show_legend:
		plt.legend(od.keys(), loc='upper left')
	ax = plt.axes()
	ax.set_xticks([0,10,20,50,100])
	k = 317
	plt.yticks([k,2*k,5*k,10*k,13*k],["k","2k","5k","10k","13k"])
	plt.xlabel(r'$t$')

	if not show_legend:
		for line, name in zip(ax.lines, od.keys()):
		    y = line.get_ydata()[-1]
		    ax.annotate(name, xy=(1,y), xytext=(6,0), color=line.get_color(), 
		                xycoords = ax.get_yaxis_transform(), textcoords="offset points",
		                size=10, va="center")
	if show:
		plt.show()
	if not show and save != "":
		plt.savefig(save)

def plot_merge_sim(show=True, save="", show_legend=False, use_text_font=True):
	results = bu.sim_load('merge_betas')
	# fonts
	if(use_text_font):
		plt.rcParams['mathtext.fontset'] = 'stix'
		plt.rcParams['font.family'] = 'STIXGeneral'

	od = OrderedDict(sorted(results.items()))
	x = np.arange(101)
	for key,val in od.iteritems():
		plt.plot(x,val,linewidth=0.7)
	if show_legend:
		plt.legend(od.keys(), loc='upper left')
	ax = plt.axes()
	ax.set_xticks([0,10,20,50,100])
	k = 317
	plt.yticks([k,2*k,5*k,10*k,13*k],["k","2k","5k","10k","13k"])
	plt.xlabel(r'$t$')

	if not show_legend:
		for line, name in zip(ax.lines, od.keys()):
		    y = line.get_ydata()[-1]
		    ax.annotate(name, xy=(1,y), xytext=(6,0), color=line.get_color(), 
		                xycoords = ax.get_yaxis_transform(), textcoords="offset points",
		                size=10, va="center")
	if show:
		plt.show()
	if not show and save != "":
		plt.savefig(save)


def plot_association(show=True, save="", use_text_font=True):
	results = bu.sim_load('association_results')
	if(use_text_font):
		plt.rcParams['mathtext.fontset'] = 'stix'
		plt.rcParams['font.family'] = 'STIXGeneral'

	od = OrderedDict(sorted(results.items()))
	plt.plot(od.keys(),od.values(),linewidth=0.7)
	ax = plt.axes()
	plt.yticks([0.1,0.2,0.3,0.4,0.5],["10%","20%","30%","40%","50%"])
	plt.xlabel(r'$t$')
	if show:
		plt.show()
	if not show and save != "":
		plt.savefig(save)

def plot_pattern_com(show=True, save="", use_text_font=True):
	results = bu.sim_load('pattern_com_iterations')
	if(use_text_font):
		plt.rcParams['mathtext.fontset'] = 'stix'
		plt.rcParams['font.family'] = 'STIXGeneral'

	od = OrderedDict(sorted(results.items()))
	plt.plot(od.keys(),od.values(),linewidth=0.7)
	ax = plt.axes()
	plt.yticks([0,0.25,0.5,0.75,1],["0%","25%","50%","75%","100%"])
	plt.xlabel(r'$t$')
	if show:
		plt.show()
	if not show and save != "":
		plt.savefig(save)

def plot_overlap(show=True, save="", use_text_font=True):
	results = bu.sim_load('overlap_results')
	if(use_text_font):
		plt.rcParams['mathtext.fontset'] = 'stix'
		plt.rcParams['font.family'] = 'STIXGeneral'

	od = OrderedDict(sorted(results.items()))
	plt.plot(od.keys(),od.values(),linewidth=0.7)
	ax = plt.axes()
	plt.xticks([0,0.2,0.4,0.6,0.8],["","20%","40%","60%","80%"])
	plt.xlabel('overlap (assemblies)')
	plt.yticks([0,0.05,0.1,0.15,0.2,0.25,0.3],["","5%","10%","15%","20%","25%","30%"])
	plt.ylabel('overlap (projections)')
	if show:
		plt.show()
	if not show and save != "":
		plt.savefig(save)

def density(n=100000,k=317,p=0.01,beta=0.05,rounds=20):
	b = brain.Brain(p)
	b.add_stimulus("stim",k)
	b.add_area("A",n,k,beta)
	b.project({"stim":["A"]},{})
	saved_w = []
	for i in range(rounds):
		b.project({"stim":["A"]},{"A":["A"]})
		saved_w.append(b.areas["A"].w)
	conn = b.connectomes["A"]["A"]
	final_winners = b.areas["A"].winners
	edges = 0
	for i in final_winners:
		for j in final_winners:
			if conn[i][j] != 0:
				edges += 1
	return float(edges)/float(k**2), saved_w

def density_sim(n=100000,k=317,p=0.01,beta_values=[0,0.025,0.05,0.075,0.1]):
	results = {}
	for beta in beta_values:
		print("Working on " + str(beta) + "\n")
		out = density(n,k,p,beta)
		results[beta] = out
	return results

def plot_density_ee(show=True,save="",use_text_font=True):
	if(use_text_font):
		plt.rcParams['mathtext.fontset'] = 'stix'
		plt.rcParams['font.family'] = 'STIXGeneral'
	od = bu.sim_load('density_results')
	plt.xlabel(r'$\beta$')
	plt.ylabel(r'assembly $p$')
	plt.plot(od.keys(),od.values(),linewidth=0.7)
	plt.plot([0,0.06],[0.01,0.01],color='red',linestyle='dashed',linewidth=0.7)
	if show:
		plt.show()
	if not show and save != "":
		plt.savefig(save)


# For default values, first B->A gets only 25% of A's original assembly
# After subsequent recurrent firings restore up to 42% 
# With artificially high beta, can get 100% restoration.
def fixed_assembly_recip_proj(n=100000, k=317, p=0.01, beta=0.05):
	b = brain.Brain(p, save_winners=True)
	b.add_stimulus("stimA",k)
	b.add_area("A",n,k,beta)
	# Will project fixes A into B
	b.add_area("B",n,k,beta)
	b.project({"stimA":["A"]},{})
	print("A.w=" + str(b.areas["A"].w))
	for i in range(20):
		b.project({"stimA":["A"]}, {"A":["A"]})
		print("A.w=" + str(b.areas["A"].w))
	# Freeze assembly in A and start projecting A <-> B
	b.areas["A"].fix_assembly()
	b.project({}, {"A":["B"]})
	for i in range(20):
		b.project({}, {"A":["B"], "B":["A","B"]})
		print("B.w=" + str(b.areas["B"].w))
	# If B has stabilized, this implies that the A->B direction is stable.
	# Therefore to test that this "worked" we should check that B->A restores A
	print("Before B->A, A.w=" + str(b.areas["A"].w))
	b.areas["A"].unfix_assembly()
	b.project({},{"B":["A"]})
	print("After B->A, A.w=" + str(b.areas["A"].w))
	for i in range(20):
		b.project({}, {"B":["A"],"A":["A"]})
		print("A.w=" + str(b.areas["A"].w))
	overlaps = bu.get_overlaps(b.areas["A"].saved_winners[-22:],0,percentage=True)
	print(overlaps)


def fixed_assembly_merge(n=100000, k=317, p=0.01, beta=0.05):
	b = brain.Brain(p)
	b.add_stimulus("stimA",k)
	b.add_stimulus("stimB",k)
	b.add_area("A",n,k,beta)
	b.add_area("B",n,k,beta)
	b.add_area("C",n,k,beta)
	b.project({"stimA":["A"], "stimB":["B"]},{})
	for i in range(20):
		b.project({"stimA":["A"], "stimB":["B"]},
			{"A":["A"], "B":["B"]})
	b.areas["A"].fix_assembly()
	b.areas["B"].fix_assembly()

def separate(n=10000, k=100, p=0.01, beta=0.05, rounds=10, overlap=0):
	b = brain.Brain(p)
	b.add_explicit_area("EXP", 2*k, k, beta)
	b.add_area("A",n,k,beta)

	b.areas["EXP"].winners = list(range(0, k))
	b.areas["EXP"].fix_assembly()

	print("PROJECTION STIM_1 INTO A....")
	b.project({}, {"EXP": ["A"]})
	prev_w = k
	print(prev_w)
	for i in range(rounds):
		b.project({}, {"EXP": ["A"], "A": ["A"]})
		new_w = b.areas["A"].w - prev_w
		print(new_w)
		prev_w = b.areas["A"].w
	stim1_assembly = b.areas["A"].winners

	print("PROJECTION STIM_2 INTO A....")


	b.areas["EXP"].winners = list(range(k-overlap, 2*k-overlap))
	b.areas["EXP"].fix_assembly()

	b.project({}, {"EXP": ["A"]})
	new_w = b.areas["A"].w - prev_w
	print(new_w)
	prev_w = b.areas["A"].w

	for i in range(rounds):
		b.project({}, {"EXP": ["A"], "A": ["A"]})
		new_w = b.areas["A"].w - prev_w
		print(new_w)
		prev_w = b.areas["A"].w
	stim2_assembly = b.areas["A"].winners
	o = bu.overlap(stim1_assembly, stim2_assembly)
	print("Got overlap of " + str(o) + " / " + str(k))
	
	b.no_plasticity = True
	b.areas["EXP"].winners = list(range(0, k))
	b.areas["EXP"].fix_assembly()
	b.project({}, {"EXP": ["A"]})
	o = bu.overlap(b.areas["A"].winners, stim1_assembly)
	print("Restored " + str(o) + " / " + str(k) + " of Assembly 1")

	b.areas["EXP"].winners = list(range(k-overlap, 2*k-overlap))
	b.project({}, {"EXP": ["A"]})
	o = bu.overlap(b.areas["A"].winners, stim2_assembly)
	print("Restored " + str(o) + " / " + str(k) + " of Assembly 2")